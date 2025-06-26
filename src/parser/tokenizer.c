#include "../../includes/minishell.h"

// Funções auxiliares
int is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

// Função para determinar o tipo de token baseado no valor
static TokenType get_token_type(const char *value)
{
	size_t len = ft_strlen(value);
	
	if (len == 1 && ft_strncmp(value, "|", 1) == 0)
		return (PIPE);
	else if (len == 1 && ft_strncmp(value, "<", 1) == 0)
		return (REDIR_IN);
	else if (len == 1 && ft_strncmp(value, ">", 1) == 0)
		return (REDIR_OUT);
	else if (len == 2 && ft_strncmp(value, "<<", 2) == 0)
		return (HEREDOC);
	else if (len == 2 && ft_strncmp(value, ">>", 2) == 0)
		return (APPEND);
	else
		return (WORD);
}

// Declaração forward
static char *expand_variable(const char *var_name);

// Função para expandir variáveis dentro de aspas duplas
static char *expand_in_double_quotes(const char *content)
{
	char *result;
	char *expanded;
	char *var_name;
	int i = 0;
	int len = 0;
	int result_len = 0;
	int var_start;
	
	// Primeira passagem: calcula tamanho necessário
	result_len = ft_strlen(content) * 2; // Estimativa
	result = malloc(result_len);
	if (!result)
		return (NULL);
	result[0] = '\0';
	
	while (content[i])
	{
		if (content[i] == '$' && content[i + 1] && content[i + 1] != ' ')
		{
			i++; // Pula o $
			var_start = i;
			len = 0;
			
			// Conta caracteres da variável
			while (content[i] && (ft_isalnum(content[i]) || content[i] == '_' || content[i] == '?'))
			{
				i++;
				len++;
			}
			
			// Extrai nome da variável
			var_name = malloc(len + 1);
			if (var_name)
			{
				ft_strlcpy(var_name, &content[var_start], len + 1);
				expanded = expand_variable(var_name);
				if (expanded)
				{
					ft_strlcat(result, expanded, result_len);
					free(expanded);
				}
				free(var_name);
			}
		}
		else
		{
			// Adiciona caractere normal
			len = ft_strlen(result);
			result[len] = content[i];
			result[len + 1] = '\0';
			i++;
		}
	}
	
	return (result);
}

// Função para processar aspas e retornar o conteúdo entre aspas
static char *process_quotes(const char *input, int *i, char quote_char)
{
	int start = ++(*i); // Pula a primeira aspa
	int len = 0;
	char *content;
	char *result;

	// Encontra a aspa fechando
	while (input[*i] && input[*i] != quote_char)
	{
		(*i)++;
		len++;
	}

       if (input[*i] != quote_char)
       {
               printf("minishell: syntax error: unclosed quote\n");
               return (NULL);
       }

	// Aloca memória e copia o conteúdo
	content = malloc(sizeof(char) * (len + 1));
	if (!content)
		return (NULL);

	ft_strlcpy(content, &input[start], len + 1);
	(*i)++; // Pula a aspa fechando
	
	// Se aspas duplas, expande variáveis; se simples, mantém literal
	if (quote_char == '"')
	{
		result = expand_in_double_quotes(content);
		free(content);
		return (result);
	}
	else
		return (content);
}

// Função para processar metacaracteres (operadores)
static char *process_metachar(const char *input, int *i)
{
	char *result;
	int len = 1;

	// Verifica se é um operador de dois caracteres (<< ou >>)
	if ((input[*i] == '<' && input[*i + 1] == '<') ||
		(input[*i] == '>' && input[*i + 1] == '>'))
		len = 2;

	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);

	ft_strlcpy(result, &input[*i], len + 1);
	*i += len;
	return (result);
}

// Função para expandir variáveis de ambiente
static char *expand_variable(const char *var_name)
{
	char *value;
	extern int g_last_exit_status;

	if (!var_name)
		return (ft_strdup(""));

	// Variável especial $?
	if (ft_strncmp(var_name, "?", 1) == 0 && ft_strlen(var_name) == 1)
	{
		value = malloc(12); // Suficiente para um int
		if (!value)
			return (NULL);
		sprintf(value, "%d", g_last_exit_status);
		return (value);
	}

	// Variáveis de ambiente normais
	value = getenv(var_name);
	if (value)
		return (ft_strdup(value));
	else
		return (ft_strdup(""));
}

// Função para processar palavras com expansão de variáveis
static char *process_word_with_expansion(const char *input, int *i)
{
	int start = *i;
	int len = 0;
	char *result;
	char *expanded;
	char *var_name;

	// Se começa com $, expande a variável
	if (input[*i] == '$' && input[*i + 1] && input[*i + 1] != ' ')
	{
		(*i)++; // Pula o $
		start = *i;
		
		// Conta caracteres da variável
		while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_' || input[*i] == '?'))
		{
			(*i)++;
			len++;
		}

		// Extrai nome da variável
		var_name = malloc(sizeof(char) * (len + 1));
		if (!var_name)
			return (NULL);
		ft_strlcpy(var_name, &input[start], len + 1);

		// Expande a variável
		expanded = expand_variable(var_name);
		free(var_name);
		return (expanded);
	}

	// Processa palavra normal
	while (input[*i] && !is_whitespace(input[*i]) && 
		   !is_metachar(input[*i]) && !is_quote(input[*i]))
	{
		(*i)++;
		len++;
	}

	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);

	ft_strlcpy(result, &input[start], len + 1);
	return (result);
}

// Função para processar palavras normais (mantida para compatibilidade)
static char *process_word(const char *input, int *i)
{
	return (process_word_with_expansion(input, i));
}

// Função principal do lexer
Token *lexer(const char *input, int *token_count)
{
	Token *tokens;
	int capacity = 32; // Capacidade inicial
	int count = 0;
	int i = 0;

	*token_count = 0;
	if (!input)
		return (NULL);

	// TODO: alocar dinamicamente tokens
	tokens = malloc(sizeof(Token) * capacity);
	if (!tokens)
		return (NULL);

	while (input[i])
	{
		// Pula espaços em branco
		while (input[i] && is_whitespace(input[i]))
			i++;

		if (!input[i])
			break;

		// Realoca se necessário
		if (count >= capacity)
		{
			capacity *= 2;
			tokens = realloc(tokens, sizeof(Token) * capacity);
			if (!tokens)
				return (NULL); // TODO: liberar memória em caso de erro
		}

		// Processa diferentes tipos de tokens
		if (is_quote(input[i]))
		{
			// TODO: implementar leitura de aspas simples e duplas
			char quote_char = input[i];
			tokens[count].value = process_quotes(input, &i, quote_char);
			if (!tokens[count].value)
			{
				// TODO: liberar memória em caso de erro
				free_tokens(tokens, count);
				return (NULL);
			}
			tokens[count].type = WORD;
		}
		else if (is_metachar(input[i]))
		{
			tokens[count].value = process_metachar(input, &i);
			if (!tokens[count].value)
			{
				free_tokens(tokens, count);
				return (NULL);
			}
			tokens[count].type = get_token_type(tokens[count].value);
		}
		else
		{
			tokens[count].value = process_word(input, &i);
			if (!tokens[count].value)
			{
				free_tokens(tokens, count);
				return (NULL);
			}
			tokens[count].type = WORD;
		}
		count++;
	}

	*token_count = count;
	return (tokens);
}

// Função para liberar tokens
void free_tokens(Token *tokens, int token_count)
{
	int i;

	if (!tokens)
		return;

	i = 0;
	while (i < token_count)
	{
		if (tokens[i].value)
			free(tokens[i].value);
		i++;
	}
	free(tokens);
} 