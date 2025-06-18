/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidos-sa <tidos-sa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:42:33 by tidos-sa          #+#    #+#             */
/*   Updated: 2024/09/27 20:37:59 by tidos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	char *ptr_str1;
	char *ptr_str2;
	unsigned int i;

	ptr_str1 = (char *)src;
	ptr_str2 = (char *)dest;

	i = 0;

	while(i < n)
	{
		ptr_str2[i] = ptr_str1[i];
		i++;
	}
	return dest;
}
/*int main(void)
{
	char dest[10];
	char *src = "hellomanos";

	ft_memcpy(dest,src,10);

	printf("%s",dest);

	return 0;
}*/
