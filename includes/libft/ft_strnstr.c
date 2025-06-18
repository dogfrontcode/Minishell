#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char *ft_strnstr(const char *big, const char *little, size_t len)
{
    size_t i = 0;
    size_t j;

    if (len == 0)
        return NULL;

    while (big[i] != '\0' && i < len)
    {
        j = 0;
        while (little[j] != '\0' && (i + j) < len && big[i + j] == little[j])
        {
            j++;
        }
        if (little[j] == '\0' && i + j <= len)
        {
            char *result = malloc(j + 1);
            if (result)
            {
                size_t k = 0;
                while (k < j)
                {
                    result[k] = big[i + k];
                    k++;
                }
                result[j] = '\0';
                return result;
            }
        }
        i++;
    }
    return NULL;
}

/*
int main()
{
    const char big[] = "hello meus amigos";
    const char little[] = "meus";

    char *result = ft_strnstr(big, little, sizeof(big));
    if (result)
    {
        printf("%s\n", result);
        free(result);
    }
    else
    {
        printf("Substring not found\n");
    }

    return 0;
}

*/
