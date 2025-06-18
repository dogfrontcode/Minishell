#include <stdlib.h>
#include "libft.h"

char *ft_substr(char const *s, unsigned int start, size_t len) {
    size_t i = 0;
    size_t s_len = 0;
    char *substr;

    
    if (!s)
        return NULL;

    while (s[s_len] != '\0')
        s_len++;

    
    if (start >= s_len)
        len = 0;

    if (len > s_len - start)
        len = s_len - start;


    substr = (char *)malloc(sizeof(char) * (len + 1));
    
    if (!substr)
        return NULL;

    while (i < len && s[start + i] != '\0') {
        substr[i] = s[start + i];
        i++;
    }

    substr[i] = '\0';

    return substr;
}
/*
int main() {
    // Teste 1: String normal
    char *str1 = "Hello, World!";
    char *result1 = ft_substr(str1, 7, 5);
    printf("Teste 1: '%s'\n", result1);
    free(result1); // Libera a memória alocada

    return 0;
}

*/