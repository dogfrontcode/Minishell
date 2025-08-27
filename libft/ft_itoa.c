/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mide-lim <mide-lim@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 21:21:52 by mide-lim          #+#    #+#             */
/*   Updated: 2024/10/21 14:43:53 by mide-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbr_len(long int nbr)
{
	size_t	len;

	len = 0;
	if (nbr <= 0)
		len++;
	while (nbr)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	long int	nbr_;
	size_t		len;
	size_t		i;
	char		*s;

	nbr_ = nbr;
	len = ft_nbr_len(nbr);
	i = len - 1;
	s = (char *)ft_calloc((len + 1), sizeof(char));
	if (!s)
		return (NULL);
	if (nbr_ < 0)
	{
		s[0] = '-';
		nbr_ *= -1;
	}
	if (nbr_ == 0)
		s[0] = '0';
	while (nbr_)
	{
		s[i--] = (nbr_ % 10) + 48;
		nbr_ /= 10;
	}
	return (s);
}
