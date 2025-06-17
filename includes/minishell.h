#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

// Máximo permitido: 1 variável global (externa)
extern volatile sig_atomic_t	g_signal;

void	init_signals(void);
void	handle_prompt(char *input);

#endif
