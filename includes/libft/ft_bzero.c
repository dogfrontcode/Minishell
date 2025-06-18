/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:16:08 by tidos-sa          #+#    #+#             */
/*   Updated: 2024/10/20 19:00:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_bzero(void *s, size_t n)
{
	char *ptr;
	size_t i;

	ptr = (char *)s;
	i = 0;

	while(i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

/*
#include <stdio.h>

int main(void)
{
	char buffer[10];
	unsigned int n = 10;

	int a;
	a = 0;

	ft_bzero(buffer,n);

	while(a < sizeof(buffer))
	{
		printf("%d",buffer[a]);
		a++;
	}
	return 0;
}

*/
