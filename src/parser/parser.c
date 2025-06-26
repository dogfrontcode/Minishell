#include "../../includes/minishell.h"

// Função para verificar se um comando é válido (built-in ou externo)
static int      command_in_path(char *cmd_name)
{
       char    *path_env;
       char    **dirs;
       char    *tmp;
       char    *full;
       int             i;

       path_env = getenv("PATH");
       if (!path_env)
               return (0);
       dirs = ft_split(path_env, ':');
       if (!dirs)
               return (0);
       i = 0;
       while (dirs[i])
       {
               tmp = ft_strjoin(dirs[i], "/");
               if (!tmp)
                       break ;
               full = ft_strjoin(tmp, cmd_name);
               free(tmp);
               if (!full)
                       break ;
               if (access(full, F_OK) == 0)
               {
                       int j = 0;
                       while (dirs[j])
                               free(dirs[j++]);
                       free(dirs);
                       free(full);
                       return (1);
               }
               free(full);
               i++;
       }
       i = 0;
       while (dirs[i])
               free(dirs[i++]);
       free(dirs);
       return (0);
}

static int is_valid_command(char *cmd_name)
{
       if (!cmd_name)
               return (0);

       if (is_builtin(cmd_name))
               return (1);

       if (ft_strchr(cmd_name, '/'))
               return (access(cmd_name, F_OK) == 0);

       return (command_in_path(cmd_name));
}

// Função para converter TokenType em RedirType
static RedirType token_to_redir_type(TokenType token_type)
{
	if (token_type == REDIR_IN)
		return (IN);
	else if (token_type == REDIR_OUT)
		return (OUT);
	else if (token_type == APPEND)
		return (APPEND_OUT);
	else if (token_type == HEREDOC)
		return (HEREDOC_TYPE);
	else
		return (IN); // Valor padrão (não deveria acontecer)
}

// Função para validar sintaxe básica
static int validate_syntax(Token *tokens, int token_count)
{
	int i;
	int has_command_in_group = 0;

	if (token_count == 0)
		return (1);

	// Verifica se começa ou termina com pipe
	if (tokens[0].type == PIPE || tokens[token_count - 1].type == PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}

	i = 0;
	while (i < token_count)
	{
		// Verifica pipes consecutivos
		if (tokens[i].type == PIPE && i + 1 < token_count && 
			tokens[i + 1].type == PIPE)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (0);
		}

		// Verifica se há comando antes do pipe
		if (tokens[i].type == PIPE)
		{
			if (!has_command_in_group)
			{
				printf("minishell: syntax error: missing command before pipe\n");
				return (0);
			}
			has_command_in_group = 0; // Reset para próximo grupo
		}
		else if (tokens[i].type == WORD)
		{
					// Se é a primeira WORD do grupo, deve ser um comando válido
		if (!has_command_in_group)
		{
			// Validação completa de comando
			if (!is_valid_command(tokens[i].value))
			{
				printf("minishell: %s: command not found\n", tokens[i].value);
				return (0);
			}
			has_command_in_group = 1;
		}
		}

		// Verifica redirecionadores sem arquivo alvo
		if ((tokens[i].type == REDIR_IN || tokens[i].type == REDIR_OUT ||
			 tokens[i].type == APPEND || tokens[i].type == HEREDOC) &&
			(i + 1 >= token_count || tokens[i + 1].type != WORD))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (0);
		}

		// Verifica redirecionador seguido de pipe
		if ((tokens[i].type == REDIR_IN || tokens[i].type == REDIR_OUT ||
			 tokens[i].type == APPEND || tokens[i].type == HEREDOC) &&
			i + 1 < token_count && tokens[i + 1].type == PIPE)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (0);
		}

		i++;
	}

	// Verifica se o último grupo tem comando
	if (!has_command_in_group && token_count > 0)
	{
		printf("minishell: syntax error: missing command\n");
		return (0);
	}

	return (1);
}

// Função para contar comandos (separados por pipes)
static int count_commands(Token *tokens, int token_count)
{
	int cmd_count = 1;
	int i = 0;

	while (i < token_count)
	{
		if (tokens[i].type == PIPE)
			cmd_count++;
		i++;
	}
	return (cmd_count);
}

// Função para inicializar um comando
static void init_command(Command *cmd)
{
	cmd->args = malloc(sizeof(char *));
	if (cmd->args)
		cmd->args[0] = NULL;
	cmd->arg_count = 0;
	cmd->redirs = NULL;
	cmd->redir_count = 0;
}

// Função para adicionar argumento a um comando
static int add_argument(Command *cmd, char *arg)
{
	char **new_args;
	
	new_args = realloc(cmd->args, sizeof(char *) * (cmd->arg_count + 2));
	if (!new_args)
		return (0);
	
	cmd->args = new_args;
	cmd->args[cmd->arg_count] = ft_strdup(arg);
	if (!cmd->args[cmd->arg_count])
		return (0);
	
	cmd->arg_count++;
	cmd->args[cmd->arg_count] = NULL; // Termina array com NULL para execve
	return (1);
}

// Função para adicionar redirecionamento a um comando
static int add_redirect(Command *cmd, RedirType type, char *filename)
{
	Redirect *new_redirs;
	
	new_redirs = realloc(cmd->redirs, sizeof(Redirect) * (cmd->redir_count + 1));
	if (!new_redirs)
		return (0);
	
	cmd->redirs = new_redirs;
	cmd->redirs[cmd->redir_count].type = type;
	cmd->redirs[cmd->redir_count].filename = ft_strdup(filename);
	if (!cmd->redirs[cmd->redir_count].filename)
		return (0);
	
	cmd->redir_count++;
	return (1);
}

// Função para processar tokens de um comando
static int process_command_tokens(Command *cmd, Token *tokens, int start, int end)
{
	int i = start;

	while (i < end)
	{
		if (tokens[i].type == WORD)
		{
			if (!add_argument(cmd, tokens[i].value))
				return (0);
		}
		else if (tokens[i].type == REDIR_IN || tokens[i].type == REDIR_OUT ||
				 tokens[i].type == APPEND || tokens[i].type == HEREDOC)
		{
			// O próximo token deve ser o filename
			if (i + 1 < end && tokens[i + 1].type == WORD)
			{
				RedirType redir_type = token_to_redir_type(tokens[i].type);
				if (!add_redirect(cmd, redir_type, tokens[i + 1].value))
					return (0);
				i++; // Pula o filename
			}
			else
			{
				// Erro de sintaxe - já foi validado antes
				return (0);
			}
		}
		i++;
	}
	return (1);
}

// Função principal do parser
Command *parser(Token *tokens, int token_count, int *cmd_count)
{
	Command *commands;
	int cmd_index = 0;
	int start = 0;
	int i = 0;

	*cmd_count = 0;
	if (!tokens || token_count == 0)
		return (NULL);

	// Valida sintaxe
	if (!validate_syntax(tokens, token_count))
		return (NULL);

	// Conta comandos
	*cmd_count = count_commands(tokens, token_count);

	// TODO: alocar dinamicamente Commands
	commands = malloc(sizeof(Command) * (*cmd_count));
	if (!commands)
		return (NULL);

	// Inicializa comandos
	i = 0;
	while (i < *cmd_count)
	{
		init_command(&commands[i]);
		i++;
	}

	// Processa tokens agrupando por comando
	i = 0;
	while (i <= token_count)
	{
		// Encontra o fim do comando atual (próximo pipe ou fim dos tokens)
		if (i == token_count || tokens[i].type == PIPE)
		{
			// Processa tokens do comando atual
			if (!process_command_tokens(&commands[cmd_index], tokens, start, i))
			{
				// TODO: liberar memória em caso de erro
				free_commands(commands, *cmd_count);
				return (NULL);
			}
			cmd_index++;
			start = i + 1; // Próximo comando começa após o pipe
		}
		i++;
	}

	return (commands);
}

// Função para liberar comandos
void free_commands(Command *commands, int cmd_count)
{
	int i, j;

	if (!commands)
		return;

	i = 0;
	while (i < cmd_count)
	{
		// Libera argumentos
		if (commands[i].args)
		{
			j = 0;
			while (j < commands[i].arg_count)
			{
				if (commands[i].args[j])
					free(commands[i].args[j]);
				j++;
			}
			free(commands[i].args);
		}

		// Libera redirecionamentos
		if (commands[i].redirs)
		{
			j = 0;
			while (j < commands[i].redir_count)
			{
				if (commands[i].redirs[j].filename)
					free(commands[i].redirs[j].filename);
				j++;
			}
			free(commands[i].redirs);
		}
		i++;
	}
	free(commands);
} 