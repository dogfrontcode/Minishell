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

// Função para processar aspas e retornar o conteúdo entre aspas
static char *process_quotes(const char *input, int *i, char quote_char)
{
	int start = ++(*i); // Pula a primeira aspa
	int len = 0;
	char *result;

	// Encontra a aspa fechando
	while (input[*i] && input[*i] != quote_char)
	{
		(*i)++;
		len++;
	}

	// TODO: Verificar se as aspas foram fechadas
	if (input[*i] != quote_char)
	{
		// Erro: aspas não fechadas
		return (NULL);
	}

	// Aloca memória e copia o conteúdo
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);

	ft_strlcpy(result, &input[start], len + 1);
	(*i)++; // Pula a aspa fechando
	return (result);
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

// Função para processar palavras normais
static char *process_word(const char *input, int *i)
{
	int start = *i;
	int len = 0;
	char *result;

	// Conta caracteres até encontrar espaço ou metacaractere
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