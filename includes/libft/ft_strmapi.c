#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*str;

	i = 0;
	len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (len > i)
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[len] = '\0';
	return (str);
}