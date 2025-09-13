/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Global shell instance for signal handling */
t_shell	*g_shell = NULL;



/* Initialize shell structure and environment */
void	init_shell(t_shell *shell, char **envp)
{
	shell->env = copy_env(envp);
	shell->last_exit = 0;
	shell->in_pipe = 0;
	shell->interrupted = 0;
	shell->interactive = isatty(STDIN_FILENO);
	g_shell = shell;
	if (shell->interactive)
		setup_signals(SIG_MODE_INTERACTIVE);
}

/* Main shell loop - Phase 1: Loop/Prompt & History */
void	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		if (shell->interactive)
			line = readline(PROMPT);
		else
		{
			line = get_next_line(STDIN_FILENO);
			if (line && ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
		}
		if (!line)
			break ;
		if (*line && shell->interactive)
			add_history(line);
		if (*line)
			shell->last_exit = process_line(shell, line);
		free(line);
	}
	if (shell->interactive)
		ft_putendl_fd("exit", STDERR_FD);
}

/* Process a single command line */
int	process_line(t_shell *shell, char *line)
{
	t_lexer		*lexer;
	t_token		*tokens;
	t_ast_node	*ast;
	int			status;

	// Phase 2: Lexer - Scanner char by char
	lexer = init_lexer(line);
	if (!lexer)
		return (ERROR);
	
	// Phase 3: Tokenization
	tokens = lexer_scan(lexer);
	free_lexer(lexer);
	if (!tokens)
		return (ERROR);
	
	// Phase 4: Expansion (happens inside parser for now)
	// Phase 5: Parser - Build AST
	if (!validate_syntax(tokens))
	{
		ft_putendl_fd("minishell: syntax error", STDERR_FD);
		free_tokens(tokens);
		return (ERROR_SYNTAX);
	}
	
	ast = parse_tokens(tokens);
	free_tokens(tokens);
	if (!ast)
		return (ERROR);
	
	// Phase 6-10: Execution
	status = execute_ast(shell, ast);
	free_ast(ast);
	return (status);
}

/* Clean up shell resources */
void	cleanup_shell(t_shell *shell)
{
	if (shell->env)
		free_env(shell->env);
	g_shell = NULL;
}


int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	shell_loop(&shell);
	cleanup_shell(&shell);
	return (shell.last_exit);
}
