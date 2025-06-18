#include "libft.h"
#include <string.h>

char *ft_strdup(const char *s) {
    size_t i = 0;
    char *copy;

    // Aloca memória suficiente para a nova string
    copy = (char *)malloc(strlen(s) + 1);

    if (copy == NULL) {
        return NULL;
    }

    while (s[i]) {
        copy[i] = s[i];
        i++;
    }
    
    copy[i] = '\0';

    return copy;
}
/*
int main ()
{
    const char str[] = "hello 42!";
    printf("%s",ft_strdup(str));
}
*/
