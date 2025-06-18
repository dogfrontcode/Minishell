/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:38:36 by tidos-sa          #+#    #+#             */
/*   Updated: 2024/10/20 18:45:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strlcat(char *dst, const char *src, size_t dstsize) {
    size_t dst_len = ft_strlen(dst);
    size_t src_len = ft_strlen(src);
    size_t i = 0;

    if (dstsize <= dst_len)
        return src_len + dstsize;


    while (src[i] != '\0' && (dst_len + i) < (dstsize - 1)) {
        dst[dst_len + i] = src[i];
        i++;
    }


    dst[dst_len + i] = '\0';

    return dst_len + src_len;
}
