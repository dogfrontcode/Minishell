/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidos-sa <tidos-sa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:58:32 by tidos-sa          #+#    #+#             */
/*   Updated: 2024/09/24 14:18:20 by tidos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_isalpha(int c)
{
	if (( c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*#include <stdio.h>

int main(void)
{
    int letra = 65;
    if (ft_isalpha(letra))
    {
        printf("'%c' é uma letra.\n", letra);
    }
    else
    {
        printf("'%c' não é uma letra.\n", letra);
    }
    
    return 0;
}*/
