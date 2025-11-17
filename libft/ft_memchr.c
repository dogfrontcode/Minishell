
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	tofind;
	size_t			i;

	str = (unsigned char *)s;
	tofind = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == tofind)
			return (((void *)str) + i);
		i++;
	}
	return (NULL);
}
