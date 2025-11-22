/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_group.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidos-sa <tidos-sa@student.42.fr>          +#+  +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:26:48 by tidos-sa          #+#    #+#             */
/*   Updated: 2025/11/21 19:26:49 by tidos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Function that writes a conversion specification of type c.
 */
int	write_c(va_list args, t_options *opts)
{
	unsigned char	c;
	int				i;

	c = (unsigned char) va_arg(args, int);
	i = 0;
	if (opts->width <= 1)
		ft_putchar_fd(c, 1);
	else
	{
		if (opts->minus == '1')
			ft_putchar_fd(c, 1);
		while (i < opts->width - 1)
		{
			ft_putchar_fd(' ', 1);
			i++;
		}
		if (opts->minus == '0')
			ft_putchar_fd(c, 1);
	}
	return (i + 1);
}
