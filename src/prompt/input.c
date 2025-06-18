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



void	handle_prompt(char *input)
{
	Token *tokens;
	Command *commands;
	int token_count = 0;
	int cmd_count = 0;
	int i, j;

	if (is_empty_line(input))
		return;

	printf("\n🔍 ANÁLISE LÉXICA:\n");
	printf("Input: \"%s\"\n", input);

	// Fase 1: Lexer
	tokens = lexer(input, &token_count);
	if (!tokens)
	{
		printf("❌ Erro no lexer!\n");
		return;
	}

	printf("Tokens encontrados (%d):\n", token_count);
	for (i = 0; i < token_count; i++)
	{
		const char *type_names[] = {"WORD", "PIPE", "REDIR_IN", "REDIR_OUT", "HEREDOC", "APPEND"};
		printf("  [%d] %s: \"%s\"\n", i, type_names[tokens[i].type], tokens[i].value);
	}

	// Fase 2: Parser
	commands = parser(tokens, token_count, &cmd_count);
	if (!commands)
	{
		printf("❌ Erro no parser!\n");
		free_tokens(tokens, token_count);
		return;
	}

	printf("\n📋 COMANDOS PARSEADOS (%d):\n", cmd_count);
	for (i = 0; i < cmd_count; i++)
	{
		printf("  Comando [%d]: ", i);
		for (j = 0; j < commands[i].arg_count; j++)
		{
			printf("'%s' ", commands[i].args[j]);
		}
		if (commands[i].redir_count > 0)
		{
			printf("| Redirs: ");
			for (j = 0; j < commands[i].redir_count; j++)
			{
				const char *redir_names[] = {"IN", "OUT", "APPEND_IN", "APPEND_OUT", "HEREDOC"};
				printf("(%s -> %s) ", redir_names[commands[i].redirs[j].type], 
					commands[i].redirs[j].filename);
			}
		}
		printf("\n");
	}

	// Fase 3: Execução
	printf("\n⚡ EXECUÇÃO:\n");
	if (commands[0].redir_count > 0)
	{
		printf("🚧 Redirecionamentos ainda não implementados\n");
	}
	else
	{
		// Executa pipeline (comando único ou múltiplos comandos)
		int exit_status = execute_pipeline(commands, cmd_count);
		if (exit_status != 0 && cmd_count > 1)
		{
			printf("Pipeline executado com status: %d\n", exit_status);
		}
	}

	// Libera memória
	free_tokens(tokens, token_count);
	free_commands(commands, cmd_count);
	printf("─────────────────────────────\n");
}

