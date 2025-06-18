#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

// Função de teste para o lexer e parser
void test_lexer_parser(const char *input)
{
	Token *tokens;
	Command *commands;
	int token_count = 0;
	int cmd_count = 0;
	int i, j;

	printf("\n=== TESTE LEXER/PARSER ===\n");
	printf("Input: \"%s\"\n\n", input);

	// Fase 1: Lexer
	tokens = lexer(input, &token_count);
	if (!tokens)
	{
		printf("Erro no lexer!\n");
		return;
	}

	printf("TOKENS (%d):\n", token_count);
	for (i = 0; i < token_count; i++)
	{
		printf("  [%d] Type: %d, Value: \"%s\"\n", 
			i, tokens[i].type, tokens[i].value);
	}

	// Fase 2: Parser
	commands = parser(tokens, token_count, &cmd_count);
	if (!commands)
	{
		printf("Erro no parser!\n");
		free_tokens(tokens, token_count);
		return;
	}

	printf("\nCOMANDOS (%d):\n", cmd_count);
	for (i = 0; i < cmd_count; i++)
	{
		printf("  Comando [%d]:\n", i);
		printf("    Args (%d): ", commands[i].arg_count);
		for (j = 0; j < commands[i].arg_count; j++)
		{
			printf("\"%s\" ", commands[i].args[j]);
		}
		printf("\n    Redirs (%d): ", commands[i].redir_count);
		for (j = 0; j < commands[i].redir_count; j++)
		{
			printf("[%d -> %s] ", commands[i].redirs[j].type, 
				commands[i].redirs[j].filename);
		}
		printf("\n");
	}

	// Libera memória
	free_tokens(tokens, token_count);
	free_commands(commands, cmd_count);
	printf("=========================\n\n");
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;
	(void)envp;

	init_signals();

	printf("🐚 Minishell iniciado! Digite 'exit' para sair.\n");
	printf("📖 Comandos disponíveis: echo, pwd, env, exit\n");
	printf("🔍 A análise léxica será mostrada para cada comando.\n");
	printf("🛡️  Sinais implementados:\n");
	printf("   • ctrl-C: Novo prompt em nova linha\n");
	printf("   • ctrl-D: Sair da shell\n");
	printf("   • ctrl-\\: Não faz nada (como no Bash)\n\n");

	while (1)
	{
		// Reseta o sinal global antes de cada comando
		g_signal = 0;
		
		input = readline("minishell$ ");
		
		// ctrl-D (EOF) - sai da shell
		if (!input)
		{
			printf("exit\n");
			break;
		}
		
		// Verifica se houve interrupção por sinal
		if (g_signal == SIGINT)
		{
			// SIGINT foi tratado pelo handler, continua o loop
			free(input);
			continue;
		}
		
		// Processa comando apenas se não estiver vazio
		if (*input)
		{
			add_history(input);
			handle_prompt(input);
		}
		
		free(input);
	}
	return (0);
}
