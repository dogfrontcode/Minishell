#include "libft.h"
#include <string.h>

void *ft_calloc(size_t num_elements, size_t element_size) {

    // Calcula o tamanho total a ser alocado
    size_t total_size = num_elements * element_size;

    // Usa malloc para alocar a memória
    void *ptr = malloc(total_size);

    // Verifica se a alocação foi bem-sucedida
    if (!ptr)
        return NULL;

    // Inicializa a memória alocada com zeros
    memset(ptr, 0, total_size);

    return ptr;
}

/*
#include <stdio.h>

int main() {
    int *arr;
    size_t n = 5;

    // Aloca memória para um array de 5 inteiros e inicializa com 0
    arr = (int *)ft_calloc(n, sizeof(int));

    if (arr == NULL) {
        printf("Erro ao alocar memória\n");
        return 1;
    }

    // Exibe o conteúdo do array (todos os elementos devem ser 0)
    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);  // Saída: 0 0 0 0 0
    }

    // Libera a memória alocada
    free(arr);

    return 0;
}

*/
