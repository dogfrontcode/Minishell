#include "../../includes/minishell.h"

extern int g_last_exit_status;

static char *itoa_simple(int n)
{
    char buffer[12];
    snprintf(buffer, sizeof(buffer), "%d", n);
    return ft_strdup(buffer);
}

static char *append_char(char *str, char c)
{
    char tmp[2];
    char *new_str;

    tmp[0] = c;
    tmp[1] = '\0';
    new_str = ft_strjoin(str, tmp);
    free(str);
    return new_str;
}

static char *expand_variables(const char *str)
{
    char *result;
    int i;

    result = ft_strdup("");
    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
        {
            if (str[i + 1] == '?')
            {
                char *num = itoa_simple(g_last_exit_status);
                char *tmp = ft_strjoin(result, num);
                free(result);
                result = tmp;
                free(num);
                i += 2;
                continue;
            }
            else if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
            {
                int start = i + 1;
                int len = 0;
                char *name;
                char *val;
                char *tmp;

                while (ft_isalnum(str[start + len]) || str[start + len] == '_')
                    len++;
                name = ft_substr(str, start, len);
                val = getenv(name);
                if (!val)
                    val = "";
                tmp = ft_strjoin(result, val);
                free(result);
                result = tmp;
                free(name);
                i = start + len;
                continue;
            }
        }
        result = append_char(result, str[i]);
        i++;
    }
    return result;
}

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
    char *result;

    result = ft_strdup("");
    (*i)++; // pula a aspa inicial
    while (input[*i] && input[*i] != quote_char)
    {
        if (input[*i] == '\\' && input[*i + 1])
        {
            if (input[*i + 1] == quote_char || input[*i + 1] == '$' || input[*i + 1] == '\\')
            {
                result = append_char(result, input[*i + 1]);
                *i += 2;
                continue;
            }
        }
        if (quote_char == '"' && input[*i] == '$')
        {
            if (input[*i + 1] == '?')
            {
                char *num = itoa_simple(g_last_exit_status);
                char *tmp = ft_strjoin(result, num);
                free(result);
                result = tmp;
                free(num);
                *i += 2;
                continue;
            }
            else if (ft_isalpha(input[*i + 1]) || input[*i + 1] == '_')
            {
                int start = *i + 1;
                int len = 0;
                char *name;
                char *val;

                while (ft_isalnum(input[start + len]) || input[start + len] == '_')
                    len++;
                name = ft_substr(input, start, len);
                val = getenv(name);
                if (!val)
                    val = "";
                char *tmp2 = ft_strjoin(result, val);
                free(result);
                result = tmp2;
                free(name);
                *i = start + len;
                continue;
            }
        }
        result = append_char(result, input[*i]);
        (*i)++;
    }
    if (input[*i] != quote_char)
    {
        printf("minishell: unclosed quote\n");
        free(result);
        return NULL;
    }
    (*i)++; // pula a aspa final
    return result;
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
    char *result;

    result = ft_strdup("");
    while (input[*i] && !is_whitespace(input[*i]) &&
           !is_metachar(input[*i]) && !is_quote(input[*i]))
    {
        result = append_char(result, input[*i]);
        (*i)++;
    }
    char *expanded = expand_variables(result);
    free(result);
    return expanded;
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