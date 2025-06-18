#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	print_test_tokens(Token *tokens, int token_count)
{
	int	i;

	printf("TOKENS (%d):\n", token_count);
	i = 0;
	while (i < token_count)
	{
		printf("  [%d] Type: %d, Value: \"%s\"\n", 
			i, tokens[i].type, tokens[i].value);
		i++;
	}
}

static void	print_test_commands(Command *commands, int cmd_count)
{
	int	i;
	int	j;

	printf("\nCOMANDOS (%d):\n", cmd_count);
	i = 0;
	while (i < cmd_count)
	{
		printf("  Comando [%d]:\n", i);
		printf("    Args (%d): ", commands[i].arg_count);
		j = 0;
		while (j < commands[i].arg_count)
		{
			printf("\"%s\" ", commands[i].args[j]);
			j++;
		}
		printf("\n    Redirs (%d): ", commands[i].redir_count);
		j = 0;
		while (j < commands[i].redir_count)
		{
			printf("[%d -> %s] ", commands[i].redirs[j].type, 
				commands[i].redirs[j].filename);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	test_lexer_parser(const char *input)
{
	Token		*tokens;
	Command		*commands;
	int			token_count;
	int			cmd_count;

	token_count = 0;
	cmd_count = 0;
	printf("\n=== TESTE LEXER/PARSER ===\n");
	printf("Input: \"%s\"\n\n", input);
	tokens = lexer(input, &token_count);
	if (!tokens)
	{
		printf("Erro no lexer!\n");
		return ;
	}
	print_test_tokens(tokens, token_count);
	commands = parser(tokens, token_count, &cmd_count);
	if (!commands)
	{
		printf("Erro no parser!\n");
		free_tokens(tokens, token_count);
		return ;
	}
	print_test_commands(commands, cmd_count);
	free_tokens(tokens, token_count);
	free_commands(commands, cmd_count);
	printf("=========================\n\n");
}

static void	print_welcome_message(void)
{
	printf("🐚 Minishell iniciado! Digite 'exit' para sair.\n");
	printf("📖 Comandos disponíveis: echo, pwd, env, exit\n");
	printf("🔍 A análise léxica será mostrada para cada comando.\n");
	printf("🛡️  Sinais implementados:\n");
	printf("   • ctrl-C: Novo prompt em nova linha\n");
	printf("   • ctrl-D: Sair da shell\n");
	printf("   • ctrl-\\: Não faz nada (como no Bash)\n\n");
}

static int	handle_input(char *input)
{
	if (!input)
	{
		printf("exit\n");
		return (1);
	}
	if (g_signal == SIGINT)
	{
		free(input);
		return (0);
	}
	if (*input)
	{
		add_history(input);
		handle_prompt(input);
	}
	free(input);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;
	(void)envp;
	init_signals();
	print_welcome_message();
	while (1)
	{
		g_signal = 0;
		input = readline("minishell$ ");
		if (handle_input(input))
			break ;
	}
	return (0);
}
