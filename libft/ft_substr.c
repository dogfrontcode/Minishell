/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_group.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidos-sa <tidos-sa@student.42.fr>          +#+  +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:26:48 by tidos-sa          #+#    #+#             */
/*   Updated: 2025/11/21 19:26:49 by tidos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	size_t	len_substring;
	char	*substring;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	len_substring = len_s - (size_t)start;
	if (start > len_s)
		return ((char *)ft_calloc(1, sizeof(char)));
	if (len > len_s)
		len = len_substring + 1;
	if (len_substring > len)
		len_substring = len;
	substring = (char *)ft_calloc(len_substring + 1, sizeof(char));
	if (!substring)
		return (NULL);
	ft_strlcpy(substring, (s + start), len + 1);
	return (substring);
}
