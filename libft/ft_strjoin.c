
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		l1;
	int		l2;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	ptr = (char *)ft_calloc(l1 + l2 + 1, 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, l1);
	ft_memcpy(ptr + l1, s2, l2);
	return (ptr);
}
