void *ft_memset(void *s, int c, unsigned int n)
{
    char *ptr = (char *)s;

    unsigned i = 0;

    while(i < n)
    {
        ptr[i] = (char)c;
        i++;
    }
    return s;
}
/*
#include <stdio.h>

int main() {
    char buffer[10]; // Define um array de 10 bytes

    // Usa a função personalizada para preencher o array com o valor 65 ('A')
    ft_memset(buffer, 65, sizeof(buffer));

    // Verifica se o array foi preenchido corretamente
    unsigned int i = 0;
    while (i < sizeof(buffer)) {
        printf("%c ", buffer[i]); // Deve imprimir 'A' para cada posição
        i++;
    }

    return 0;
}
*/
