/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Phase 10: Signal Handling
 * TODO: Implement proper signal handling
 * - Different modes for interactive/executing/heredoc
 * - Ctrl-C and Ctrl-\ handling
 * - Integration with readline
 */

void	setup_signals(t_signal_mode mode)
{
	if (mode == SIG_MODE_INTERACTIVE)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SIG_MODE_EXECUTING)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == SIG_MODE_HEREDOC)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDERR_FD);
	if (g_shell)
	{
		g_shell->interrupted = 1;
		g_shell->last_exit = 130;
	}
	// Reset readline when in interactive mode
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit: 3\n", STDERR_FD);
	if (g_shell)
		g_shell->last_exit = 131;
}

void	disable_echo_ctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FD, &term) == 0)
	{
		term.c_lflag &= ~(ECHOCTL);
		tcsetattr(STDIN_FD, TCSANOW, &term);
	}
}

void	enable_echo_ctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FD, &term) == 0)
	{
		term.c_lflag |= ECHOCTL;
		tcsetattr(STDIN_FD, TCSANOW, &term);
	}
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int	get_signal_exit_code(int status)
{
	if (WIFSIGNALED(status))
		return (ERROR_SIGNAL_BASE + WTERMSIG(status));
	return (0);
}

