/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidos-sa <tidos-sa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:03:54 by tidos-sa          #+#    #+#             */
/*   Updated: 2024/10/05 16:14:21 by tidos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		c -= 32;
	}
	return c;
}
/*int main() {
    // Array de caracteres
    char input[] = {'A', 'A', '	', '!', 'e', 'E', '\0'};  // O '\0' é o terminador da string

    // Converte cada caractere do array para maiúscula
    for (int i = 0; input[i] != '\0'; i++) {
        input[i] = (char)ft_toupper((int)input[i]);
    }

    printf("A string em maiúsculas é: %s\n", input);

    return 0;
}*/
