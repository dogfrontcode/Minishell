/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:27:49 by tidos-sa          #+#    #+#             */
/*   Updated: 2024/10/20 18:38:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_isalnum(int c)
{
	if((c >= 65 && c <= 90)||(c >= 97 && c <= 122))
		return 1;
	if(c >= 48 && c <= 57)
		return 1;
	else
		return 0;
}
/*
#include <stdio.h>
int main(void)
{
	int c = 48;
	printf("%i",ft_isalnum(c));
}*/
