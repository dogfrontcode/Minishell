#include "../../includes/minishell.h"

static void	sigint_handler(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sigquit_handler(int sig)
{
	(void)sig;
	g_signal = SIGQUIT;
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
//Este é o arquivo para lidar com Ctrl+C, Ctrl+\ e Ctrl+D:
//Ctrl+\ ainda nao esta bom 