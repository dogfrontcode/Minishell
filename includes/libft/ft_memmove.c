#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*temp2;
	unsigned char	*temp;

	temp = (unsigned char *)dest;
	temp2 = (unsigned char *)src;
	if (!dest || !src)
		return (NULL);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	while (n > 0)
	{
		temp[n - 1] = temp2[n - 1];
		n--;
	}
	return (dest);
}

int main()
{


}