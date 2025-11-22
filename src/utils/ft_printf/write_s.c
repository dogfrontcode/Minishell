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
 * Helper function to write a conversion specification of type s.
 */
static int	write_s_helper(char *s, t_options *opts)
{
	int		len;
	int		i;

	len = ft_strlen(s);
	i = 0;
	if (len > opts->prec && opts->prec != -1)
		len = opts->prec;
	if (opts->width <= len)
		putstr_len(s, len);
	else
	{
		if (opts->minus == '1')
			putstr_len(s, len);
		while (i < opts->width - len)
		{
			ft_putchar_fd(' ', 1);
			i++;
		}
		if (opts->minus == '0')
			putstr_len(s, len);
	}
	return (len + i);
}

/*
 * Function that writes a conversion specification of type s.
 */
int	write_s(va_list args, t_options *opts)
{
	char	*s;
	int		i;

	s = (char *)va_arg(args, char *);
	if (s == NULL)
		i = write_s_helper("(null)", opts);
	else
		i = write_s_helper(s, opts);
	return (i);
}
