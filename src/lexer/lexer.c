/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Phase 2: Lexer - Character scanner
 * TODO: Implement character-by-character scanning
 * - Ignore spaces/tabs
 * - Detect simple and double operators
 * - Manage quote states
 */

t_lexer	*init_lexer(char *input)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->input = input;
	lexer->pos = 0;
	lexer->len = ft_strlen(input);
	lexer->state = STATE_NORMAL;
	lexer->tokens = NULL;
	return (lexer);
}

t_token	*lexer_scan(t_lexer *lexer)
{
	// TODO: Implement actual lexical analysis
	// For now, return a simple token for testing
	t_token	*token;

	token = create_token(TOKEN_WORD, ft_strdup(lexer->input));
	return (token);
}

void	free_lexer(t_lexer *lexer)
{
	if (lexer)
		free(lexer);
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

