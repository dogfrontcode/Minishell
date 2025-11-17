
#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*dest;

	len = ft_strlen(s);
	dest = (char *)malloc(len * sizeof(char) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len + 1)
	{
		dest[i] = s[i];
		i++;
	}
	return (dest);
}
