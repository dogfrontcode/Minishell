/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:23:05 by tidos-sa          #+#    #+#             */
/*   Updated: 2024/10/20 18:47:30 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strrchr(const char *s, int c)
{

	size_t len = ft_strlen(s);
	int i = len;

	while(i >= 0)
	{
		i--;
		if( s[i] == (char)c)
		{
			return (char *)&s[i];
		}
	}

	return NULL;
}


int main() {
    const char *str = "Hello, world!";
    char c = 'H';
    
    char *result = ft_strrchr(str, c);
    if (result) {
        printf("O último '%c' encontrado em \"%s\" está na posição: %ld\n", c, str, result - str);
    } else {
        printf("Caractere '%c' não encontrado em \"%s\"\n", c, str);
    }

    // Testando com um caractere que não está na string
    c = 'd';
    result = ft_strrchr(str, c);
    if (result) {
        printf("O último '%c' encontrado em \"%s\" está na posição: %ld\n", c, str, result - str);
    } else {
        printf("Caractere '%c' não encontrado em \"%s\"\n", c, str);
    }

    return 0;
}

