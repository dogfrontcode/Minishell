#include "../../includes/minishell.h"

// Handler para SIGINT (ctrl-C)
static void	sigint_handler(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	
	// Escreve nova linha
	write(STDOUT_FILENO, "\n", 1);
	
	// Limpa a linha atual do readline
	rl_on_new_line();
	
	// Exibe o novo prompt
	rl_redisplay();
}

// Handler para SIGQUIT (ctrl-\)
static void	sigquit_handler(int sig)
{
	(void)sig;
	// Em modo interativo, ctrl-\ não deve fazer nada
	// Apenas armazena o sinal na variável global
	g_signal = SIGQUIT;
}

// Configuração inicial dos sinais
void	init_signals(void)
{
	// Instala handler para SIGINT (ctrl-C)
	signal(SIGINT, sigint_handler);
	
	// Instala handler para SIGQUIT (ctrl-\)
	signal(SIGQUIT, sigquit_handler);
}

// Função para restaurar sinais padrão (para processos filhos)
void	restore_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

// Função para ignorar sinais (para processos em background)
void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

//Este é o arquivo para lidar com Ctrl+C, Ctrl+\ e Ctrl+D:
//Ctrl+\ ainda nao esta bom 