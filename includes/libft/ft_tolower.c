/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:15:20 by tidos-sa          #+#    #+#             */
/*   Updated: 2024/10/20 18:51:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c += 32;
	}
	return c;
}
/*
int main() {
    // Array de caracteres
    char input[] = {'A', 'A', ' ', '!', 'e', 'E', '\0'};  // O '\0' é o terminador da string

    // Converte cada caractere do array para maiúscula
    for (int i = 0; input[i] != '\0'; i++) {
        input[i] = (char)ft_tolower((int)input[i]);
    }

    printf("A string em maiúsculas é: %s\n", input);

    return 0;
}

*/
