/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

/* Token types - Phase 3: Tokenization */
typedef enum e_token_type
{
	TOKEN_WORD,			// Regular word/command/argument
	TOKEN_PIPE,			// | pipe operator
	TOKEN_REDIR_IN,		// < input redirection
	TOKEN_REDIR_OUT,	// > output redirection
	TOKEN_REDIR_APPEND,	// >> append redirection
	TOKEN_HEREDOC,		// << heredoc
	TOKEN_END			// End of tokens
}	t_token_type;

/* Token structure */
typedef struct s_token
{
	t_token_type		type;
	char				*value;
	int					in_single_quotes;
	int					in_double_quotes;
	struct s_token		*next;
}	t_token;

/* Token management functions */
t_token	*create_token(t_token_type type, char *value);
void	free_tokens(t_token *tokens);
void	add_token(t_token **list, t_token *new_token);
char	*token_type_to_string(t_token_type type);

#endif

