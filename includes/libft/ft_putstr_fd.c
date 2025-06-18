/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidos-sa <tidos-sa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 02:10:11 by tidos-sa          #+#    #+#             */
/*   Updated: 2024/10/09 02:18:48 by tidos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_putstr_fd(char *s, int fd)
{
    if (s == NULL)
        return;

    while (*s)
	{
        write(fd, s, 1);
        s++;
    }
}
/*
int main()
{
	char s[] = "helloooo";
	int fd = 2;
	ft_putstr_fd(s,fd);
}
*/