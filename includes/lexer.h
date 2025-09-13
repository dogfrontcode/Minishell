/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "tokens.h"

/* Lexer states - Phase 2: Character scanner */
typedef enum e_lexer_state
{
	STATE_NORMAL,
	STATE_IN_SINGLE_QUOTE,
	STATE_IN_DOUBLE_QUOTE,
	STATE_IN_WORD
}	t_lexer_state;

/* Lexer structure */
typedef struct s_lexer
{
	char			*input;
	int				pos;
	int				len;
	t_lexer_state	state;
	t_token			*tokens;
}	t_lexer;

/* Lexer functions */
t_lexer		*init_lexer(char *input);
t_token		*lexer_scan(t_lexer *lexer);
void		free_lexer(t_lexer *lexer);
int			is_operator(char c);
int			is_whitespace(char c);
int			is_quote(char c);

#endif

