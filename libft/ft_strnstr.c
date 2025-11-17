
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*s;

	i = 0;
	j = 0;
	s = (char *)big;
	if (*little == '\0')
		return (s);
	while ((i < len) && (s[i]))
	{
		k = i;
		while (little[j] && (k < len) && (s[k] == little[j]))
		{
			if (little[j + 1] == '\0')
				return (&s[i]);
			k++;
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
