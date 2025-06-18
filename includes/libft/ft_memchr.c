/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidos-sa <tidos-sa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:42:08 by tidos-sa          #+#    #+#             */
/*   Updated: 2024/10/08 22:50:45 by tidos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		target;
	size_t				i;

	ptr = (const unsigned char *)s;
	target = (unsigned char)c;
	i = 0;

	while (i < n)
	{
		if (ptr[i] == target)
		{
			return ((void *)(ptr + i));
		}
		i++;
	}

	return (NULL);
}
