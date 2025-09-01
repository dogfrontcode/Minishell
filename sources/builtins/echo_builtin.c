/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:55:59 by mcombeau          #+#    #+#             */
/*   Updated: 2022/11/03 15:48:44 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // Inclui definições do minishell

/* is_n_flag:
*       Checks whether an arg is an -n option flag.
*       Returns true if the arg is some variation of -n, -nnnn, -nn, etc.
*       Returns false if it contains anything other than - and n (ex. --n -nnnm -n1234)
*/
static bool     is_n_flag(char *arg) // Verifica se o argumento é a opção -n
{
        int     i; // Índice para percorrer a string
        bool    n_flag; // Indica se -n foi encontrado

        n_flag = false; // Inicializa flag como falso
        i = 0; // Começa no início da string
        if (arg[i] != '-') // Se primeiro caractere não for '-'
                return (n_flag); // Retorna falso
        i++; // Avança após '-'
        while (arg[i] && arg[i] == 'n') // Enquanto houver 'n'
                i++; // Continua avançando
        if (arg[i] == '\0') // Se chegou ao fim da string
                n_flag = true; // Marca que opção -n é válida
        return (n_flag); // Retorna resultado
}

/* echo_print_args:
*       Prints the given array of aruments to STDOUT.
*/
static void     echo_print_args(char **args, bool n_flag, int i) // Imprime argumentos a partir de i
{
        if (!args[i]) // Se não houver argumentos
        {
                if (!n_flag) // Se -n não foi passado
                        ft_putchar_fd('\n', STDOUT_FILENO); // Imprime nova linha
                return ; // Encerra a função
        }
        while (args[i]) // Percorre todos os argumentos restantes
        {
                ft_putstr_fd(args[i], STDOUT_FILENO); // Escreve argumento atual
                if (args[i + 1]) // Se existe próximo argumento
                        ft_putchar_fd(' ', STDOUT_FILENO); // Imprime espaço
                else if (!args[i + 1] && !n_flag) // Se último argumento e sem -n
                        ft_putchar_fd('\n', STDOUT_FILENO); // Imprime nova linha
                i++; // Avança para próximo argumento
        }
}

/* echo_builtin:
*       Executes the echo builtin command: prints the given strings
*       and adds a \n character or not depending on the -n option.
*       Returns 1 on completion.
*/
int     echo_builtin(t_data *data, char **args) // Implementação do comando echo
{
        int     i; // Índice para percorrer argumentos
        bool    n_flag; // Marca presença da opção -n

        (void)data; // Estrutura data não utilizada
        n_flag = false; // Inicializa como sem -n
        i = 1; // Começa após o nome do comando
        while (args[i] && is_n_flag(args[i])) // Processa todas as opções -n consecutivas
        {
                n_flag = true; // Indica que -n foi encontrado
                i++; // Avança para próximo argumento
        }
        echo_print_args(args, n_flag, i); // Imprime os argumentos restantes
        return (EXIT_SUCCESS); // Retorna sucesso
}

