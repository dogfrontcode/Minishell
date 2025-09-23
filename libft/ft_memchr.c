/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mide-lim <mide-lim@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:49:18 by mide-lim          #+#    #+#             */
/*   Updated: 2024/10/21 14:48:03 by mide-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	tofind;
	size_t			i;

	str = (unsigned char *)s;
	tofind = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == tofind)
			return (((void *)str) + i);
		i++;
	}
	return (NULL);
}
