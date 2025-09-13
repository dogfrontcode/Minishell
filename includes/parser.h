/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokens.h"

/* Command node types - Phase 5: AST Construction */
typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECT
}	t_node_type;

/* Redirection structure */
typedef struct s_redirect
{
	int					type;		// <, >, >>, <<
	char				*file;		// Target file
	struct s_redirect	*next;
}	t_redirect;

/* Command structure */
typedef struct s_command
{
	char				**argv;		// Command arguments
	t_redirect			*redirects;	// List of redirections
	struct s_command	*next;		// Next command in pipeline
}	t_command;

/* AST Node */
typedef struct s_ast_node
{
	t_node_type			type;
	t_command			*command;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

/* Parser functions */
t_ast_node	*parse_tokens(t_token *tokens);
t_command	*parse_command(t_token **tokens);
t_redirect	*parse_redirections(t_token **tokens);
void		free_ast(t_ast_node *node);
void		free_command(t_command *cmd);
int			validate_syntax(t_token *tokens);

#endif

