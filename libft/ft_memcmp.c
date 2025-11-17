
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*pt1;
	unsigned char	*pt2;

	if (n == 0)
		return (0);
	pt1 = (unsigned char *)s1;
	pt2 = (unsigned char *)s2;
	while ((*pt1 == *pt2) && n - 1 > 0)
	{
		pt1++;
		pt2++;
		n--;
	}
	return ((int)(*pt1 - *pt2));
}
