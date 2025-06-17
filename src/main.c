#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		init_signals();
		input = readline("minishell$ ");
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (*input)
			add_history(input);
		handle_prompt(input); // Aqui você chamará o parser + executor
		free(input);
	}
	return (0);
}
