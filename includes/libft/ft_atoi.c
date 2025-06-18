
#include "libft.h"

int ft_atoi(const char *str) {
    int i = 0;
    int sign = 1;
    int result = 0;

    // Ignora os espaços em branco no início
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
           str[i] == '\v' || str[i] == '\f' || str[i] == '\r') {
        i++;
    }

    // Verifica se há sinal (+ ou -)
    if (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-') {
            sign = -1;  // Se for '-', o número será negativo
        }
        i++;
    }

    // Converte os dígitos em um número
    while (str[i] >= '0' && str[i] <= '9') {
        int digit = str[i] - '0';  // Converte o caractere em dígito numérico

        result = result * 10 + digit;
        i++;
    }

    return result * sign;  // Aplica o sinal ao resultado final
}

/*
int main() {
    printf("%d\n", ft_atoi("   -12345"));  // Saída: -12345
    printf("%d\n", ft_atoi("1234aasswsw5"));      // Saída: 12345
    printf("%d\n", ft_atoi("   +42abc"));  // Saída: 42 (para quando encontra 'a', para a conversão)

    return 0;
}
*/