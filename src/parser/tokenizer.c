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

// Declarações forward
static char *expand_variable(const char *var_name);
static char *process_quotes(const char *input, int *i, char quote_char);

// Função para processar uma palavra composta (incluindo aspas adjacentes)
static char *process_compound_word(const char *input, int *i)
{
	char *result = ft_strdup("");
	char *temp;
	char *part;
	int start;
	
	if (!result)
		return (NULL);
	
	// Continua processando enquanto não encontrar espaço ou metacaracter
	while (input[*i] && !is_whitespace(input[*i]) && !is_metachar(input[*i]))
	{
		if (is_quote(input[*i]))
		{
			// Processa aspas
			char quote_char = input[*i];
			part = process_quotes(input, i, quote_char);
			if (!part)
			{
				free(result);
				return (NULL);
			}
		}
		else if (input[*i] == '$' && input[*i + 1] && input[*i + 1] != ' ')
		{
			// Processa variável
			(*i)++; // Pula o $
			start = *i;
			
			// Conta caracteres da variável (incluindo $? como caso especial)
			if (input[*i] == '?')
			{
				// $? sempre é tratado como variável de 1 caractere
				(*i)++;
			}
			else
			{
				// Variável normal
				while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
					(*i)++;
			}
			
			// Extrai nome da variável
			part = malloc(*i - start + 1);
			if (!part)
			{
				free(result);
				return (NULL);
			}
			ft_strlcpy(part, &input[start], *i - start + 1);
			
			// Expande variável
			temp = expand_variable(part);
			free(part);
			part = temp;
			if (!part)
				part = ft_strdup("");
		}
		else
		{
			// Processa texto normal até encontrar aspa, $, espaço ou metachar
			start = *i;
			while (input[*i] && !is_whitespace(input[*i]) && 
				   !is_metachar(input[*i]) && !is_quote(input[*i]) && input[*i] != '$')
				(*i)++;
			
			part = malloc(*i - start + 1);
			if (!part)
			{
				free(result);
				return (NULL);
			}
			ft_strlcpy(part, &input[start], *i - start + 1);
		}
		
		// Concatena a parte ao resultado
		temp = ft_strjoin(result, part);
		free(result);
		free(part);
		result = temp;
		if (!result)
			return (NULL);
	}
	
	return (result);
}

// Função para expandir variáveis dentro de aspas duplas
static char *expand_in_double_quotes(const char *content)
{
	char *result = ft_strdup("");
	char *temp;
	char *expanded;
	char *var_name;
	int i = 0;
	int len = 0;
	int var_start;
	char char_str[2];
	
	if (!result)
		return (NULL);
	
	while (content[i])
	{
		if (content[i] == '$' && content[i + 1] && content[i + 1] != ' ')
		{
			i++; // Pula o $
			var_start = i;
			len = 0;
			
			// Conta caracteres da variável (tratamento especial para $?)
			if (content[i] == '?' && (content[i + 1] == '\0' || !ft_isalnum(content[i + 1])))
			{
				// $? seguido de não-alfanumérico
				i++;
				len = 1;
			}
			else
			{
				// Variável normal
				while (content[i] && (ft_isalnum(content[i]) || content[i] == '_'))
				{
					i++;
					len++;
				}
			}
			
			// Extrai nome da variável
			var_name = malloc(len + 1);
			if (var_name)
			{
				ft_strlcpy(var_name, &content[var_start], len + 1);
				expanded = expand_variable(var_name);
				if (expanded)
				{
					temp = ft_strjoin(result, expanded);
					free(result);
					free(expanded);
					result = temp;
					if (!result)
					{
						free(var_name);
						return (NULL);
					}
				}
				free(var_name);
			}
		}
		else
		{
			// Adiciona caractere normal usando strjoin
			char_str[0] = content[i];
			char_str[1] = '\0';
			temp = ft_strjoin(result, char_str);
			free(result);
			result = temp;
			if (!result)
				return (NULL);
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
		if (is_metachar(input[i]))
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
			// Processa palavra composta (pode incluir aspas, variáveis, texto)
			tokens[count].value = process_compound_word(input, &i);
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