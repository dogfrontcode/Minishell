/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mide-lim <mide-lim@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:05:21 by mide-lim          #+#    #+#             */
/*   Updated: 2024/10/21 15:02:46 by mide-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			while (s[i] != c && s[i])
				i++;
			count++;
		}
	}
	return (count);
}

static void	ft_free(char **list)
{
	size_t	i;

	i = 0;
	while (list[i])
		free(list[i++]);
	free(list);
}

static char	**ft_fill_split(const char *s, char c, char **list)
{
	size_t	start;
	size_t	split;
	size_t	len;
	size_t	wrds;

	len = ft_strlen(s);
	start = 0;
	split = 0;
	while (s[start])
	{
		wrds = 0;
		if ((s[start] != c) && (start + wrds < len))
		{
			while ((s[start + wrds] != c) && (start + wrds < len))
				wrds++;
			list[split] = ft_substr(s, start, wrds);
			if (!list[split])
				return (ft_free(list), NULL);
			start += wrds - 1;
			split++;
		}
		start++;
	}
	return (list);
}

char	**ft_split(char const *s, char c)
{
	char	**list;
	size_t	words;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	list = (char **)ft_calloc((words + 1), sizeof(char *));
	if (!list)
		return (NULL);
	return (ft_fill_split(s, c, list));
}
