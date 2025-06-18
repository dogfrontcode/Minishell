/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidos-sa <tidos-sa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:36:06 by tidos-sa          #+#    #+#             */
/*   Updated: 2024/10/08 21:47:54 by tidos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *str;
	unsigned char *strr;
	int diff;
	size_t i;

	i = 0;
	diff = 0;
	str = (unsigned char *)s1;
	strr = (unsigned char *)s2;

	while (i < n)
	{
		if(str[i] != strr[i])
		{
			diff = (str[i] - strr[i]);

			if(diff > 0)
			 	return 1;
			if(diff < 0)
				return -1;
		}
		i++;
	}

	return 0;
}

/*int main(void) {
    char str1[] = "abcdef";
    char str2[] = "abcdeg";
    char str3[] = "abcdef";
    char str4[] = "abcde";

    // Teste 1: str1 e str2
    int result1 = ft_memcmp(str1, str2, 6);
    printf("Comparando '%s' e '%s': %d\n", str1, str2, result1);

    // Teste 2: str1 e str3
    int result2 = ft_memcmp(str1, str3, 6);
    printf("Comparando '%s' e '%s': %d\n", str1, str3, result2);

    // Teste 3: str1 e str4
    int result3 = ft_memcmp(str1, str4, 5);
    printf("Comparando '%s' e '%s': %d\n", str1, str4, result3);

    // Teste 4: str2 e str3 (comparando apenas parte)
    int result4 = ft_memcmp(str2, str3, 5);
    printf("Comparando '%s' e '%s': %d\n", str2, str3, result4);

    return 0;
}*/
