/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:22:10 by tidos-sa          #+#    #+#             */
/*   Updated: 2024/10/20 18:47:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while ( i < n && (s1[i] != '\0' || s2[i] != '\0' ))
	{
		if ( s1[i] != s2[i])
		{
			if( s1[i] < s2[i])
			{
				return -1;
			}
			else
			{
				return 1;
			}
		}
	i++;
	}
	return 0;
}

/*
int main() 
{
    const char *str1 = "Hello, World!";
    const char *str2 = "Hello, World!";
    const char *str3 = "Hello, Worlf!";
    const char *str4 = "Hello, World!";

    int result;

    // Comparando str1 e str2
    result = ft_strncmp(str1, str2, 13);
    printf("Comparando '%s' e '%s': %d\n", str1, str2, result); // Esperado: 0

    // Comparando str1 e str3
    result = ft_strncmp(str1, str3, 13);
    printf("Comparando '%s' e '%s': %d\n", str1, str3, result); // Esperado: valor negativo

    // Comparando str1 e str4 com n menor que o tamanho da string
    result = ft_strncmp(str1, str4, 5);
    printf("Comparando '%s' e '%s': %d\n", str1, str4, result); // Esperado: 0

    // Comparando com n menor que o comprimento da primeira string
    result = ft_strncmp(str1, str2, 5);
    printf("Comparando '%s' e '%s': %d\n", str1, str2, result); // Esperado: 0

    return 0;
}
*/
