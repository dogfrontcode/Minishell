/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidos-sa <tidos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:17:54 by tidos-sa          #+#    #+#             */
/*   Updated: 2024/10/09 02:36:08 by tidos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ttoupper(unsigned int c, char *str)
{

	if (str[c] >= 'a' && str[c] <= 'z')
	{
		str[c] -= 32;
       		write(1, &str[c], 1);
	}
	else
	{
		write(1, &str[c], 1);
	}

}

void    ft_striteri(char *s, void (*f)(unsigned int,char*))
{
    size_t i;

    i = 0;
    while (s[i] != '\0')
    {
    	f(0,&s[i]);
	i++;
    }
}


int main(void)
{
    char s[] = "opaaa bb";

    ft_striteri(s,ttoupper);
}
