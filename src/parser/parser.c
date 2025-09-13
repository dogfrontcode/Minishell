/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Phase 5: Parser - AST Construction
 * TODO: Build Abstract Syntax Tree
 * - Group WORDs into argv[]
 * - Associate redirections
 * - Build pipelines
 * - Validate syntax
 */

t_ast_node	*parse_tokens(t_token *tokens)
{
	// TODO: Implement actual parsing
	// For now, return NULL
	(void)tokens;
	return (NULL);
}

t_command	*parse_command(t_token **tokens)
{
	// TODO: Parse single command with its arguments
	(void)tokens;
	return (NULL);
}

t_redirect	*parse_redirections(t_token **tokens)
{
	// TODO: Parse redirections from tokens
	(void)tokens;
	return (NULL);
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->command)
		free_command(node->command);
	free(node);
}

void	free_command(t_command *cmd)
{
	t_redirect	*redir;
	t_redirect	*tmp;
	int			i;

	if (!cmd)
		return ;
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
	}
	redir = cmd->redirects;
	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		if (tmp->file)
			free(tmp->file);
		free(tmp);
	}
	free(cmd);
}

int	validate_syntax(t_token *tokens)
{
	// TODO: Implement syntax validation
	// For now, return 1 (valid)
	(void)tokens;
	return (1);
}

