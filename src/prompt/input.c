#include "../../includes/minishell.h"

static int	is_empty_line(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}

/*
static void	print_tokens(Token *tokens, int token_count)
{
	const char	*type_names[] = {"WORD", "PIPE", "REDIR_IN", 
		"REDIR_OUT", "HEREDOC", "APPEND"};
	int			i;

	printf("Tokens encontrados (%d):\n", token_count);
	i = 0;
	while (i < token_count)
	{
		printf("  [%d] %s: \"%s\"\n", i, type_names[tokens[i].type], 
			tokens[i].value);
		i++;
	}
}

static void	print_command_args(Command *cmd, int cmd_index)
{
	int	j;

	printf("  Comando [%d]: ", cmd_index);
	j = 0;
	while (j < cmd->arg_count)
	{
		printf("'%s' ", cmd->args[j]);
		j++;
	}
}

static void	print_command_redirs(Command *cmd)
{
	const char	*redir_names[] = {"IN", "OUT", "APPEND_IN", 
		"APPEND_OUT", "HEREDOC"};
	int			j;

	if (cmd->redir_count > 0)
	{
		printf("| Redirs: ");
		j = 0;
		while (j < cmd->redir_count)
		{
			printf("(%s -> %s) ", redir_names[cmd->redirs[j].type], 
				cmd->redirs[j].filename);
			j++;
		}
	}
}

static void	print_commands(Command *commands, int cmd_count)
{
	int	i;

	printf("\n📋 COMANDOS PARSEADOS (%d):\n", cmd_count);
	i = 0;
	while (i < cmd_count)
	{
		print_command_args(&commands[i], i);
		print_command_redirs(&commands[i]);
		printf("\n");
		i++;
	}
}
*/

static int	execute_commands(Command *commands, int cmd_count)
{
	int	exit_status;

	// printf("\n⚡ EXECUÇÃO:\n");
       exit_status = execute_pipeline(commands, cmd_count);
	// if (exit_status != 0 && cmd_count > 1)
	//	printf("Pipeline executado com status: %d\n", exit_status);
	return (exit_status);
}

void	handle_prompt(char *input)
{
	Token		*tokens;
	Command		*commands;
	int			token_count;
	int			cmd_count;

	token_count = 0;
	cmd_count = 0;
	if (is_empty_line(input))
		return ;
	// printf("\n🔍 ANÁLISE LÉXICA:\n");
	// printf("Input: \"%s\"\n", input);
	tokens = lexer(input, &token_count);
	if (!tokens)
	{
		// printf("❌ Erro no lexer!\n");
		return ;
	}
	// print_tokens(tokens, token_count);
	commands = parser(tokens, token_count, &cmd_count);
	if (!commands)
	{
		// printf("❌ Erro no parser!\n");
		free_tokens(tokens, token_count);
		return ;
	}
	// print_commands(commands, cmd_count);
	execute_commands(commands, cmd_count);
	free_tokens(tokens, token_count);
	free_commands(commands, cmd_count);
	// printf("─────────────────────────────\n");
}

