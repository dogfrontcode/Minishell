/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

/* Phase 10: Signal handling */

/* Signal modes */
typedef enum e_signal_mode
{
	SIG_MODE_INTERACTIVE,	// Normal prompt mode
	SIG_MODE_EXECUTING,		// During command execution
	SIG_MODE_HEREDOC		// During heredoc input
}	t_signal_mode;

/* Signal handlers */
void	setup_signals(t_signal_mode mode);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	disable_echo_ctl(void);
void	enable_echo_ctl(void);

/* Signal utilities */
void	reset_signals(void);
void	ignore_signals(void);
int		get_signal_exit_code(int status);

#endif

