#include "libft.h"

size_t ft_strlcpy(char *dst, const char *src, size_t dstsize) {
    size_t src_len = ft_strlen(src);
    size_t i = 0;

    if (dstsize > 0) {
        while (src[i] != '\0' && i < (dstsize - 1)) {
            dst[i] = src[i];
            i++;
        }

        dst[i] = '\0';
    }

    return src_len;
}