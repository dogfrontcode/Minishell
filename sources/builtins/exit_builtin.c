/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:32:33 by mcombeau          #+#    #+#             */
/*   Updated: 2022/11/05 12:17:05 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // Inclui definições do minishell

/* check_out_of_range:
*       Checks if the number goes over LONG_MAX or LONG_MIN.
*       Sets an error boolean to true if the number is out of range, false if not.
*/
static bool     check_out_of_range(int neg, unsigned long long num, bool *error) // Verifica estouro de faixa
{
        if ((neg == 1 && num > LONG_MAX) // Número positivo maior que LONG_MAX
                || (neg == -1 && num > -(unsigned long)LONG_MIN)) // Número negativo menor que LONG_MIN
                *error = true; // Marca erro
        return (*error); // Retorna estado de erro
}

/* ft_atoi_long:
*       Transforms a string comprised of digits into a long integer.
*       Returns the long integer. In case of error, sets an error boolean
*       to true.
*/
static int      ft_atoi_long(const char *str, bool *error) // Converte string em long com verificação
{
        unsigned long long      num; // Acumulador numérico
        int                     neg; // Indica sinal do número
        int                     i; // Índice da string

        num = 0; // Inicializa acumulador
        neg = 1; // Assume sinal positivo
        i = 0; // Começa no início da string
        while (str[i] && ft_isspace(str[i])) // Ignora espaços iniciais
                i++; // Avança
        if (str[i] == '+') // Se houver sinal positivo
                i++; // Avança
        else if (str[i] == '-') // Se houver sinal negativo
        {
                neg *= -1; // Ajusta sinal para negativo
                i++; // Avança
        }
        while (str[i] && ft_isdigit(str[i])) // Percorre dígitos
        {
                num = (num * 10) + (str[i] - '0'); // Atualiza acumulador
                if (check_out_of_range(neg, num, error)) // Verifica overflow/underflow
                        break ; // Interrompe se ultrapassar limite
                i++; // Avança para próximo caractere
        }
        return (num * neg); // Retorna número com sinal
}

/* get_exit_code:
*       Gets the exit code from the arguments given to the exit builtin.
*       Returns 0 if no arguments were provided.
*       Returns 2 in case argument is not digits.
*       Returns the numeric exit code on success.
*/
static int      get_exit_code(char *arg, bool *error) // Obtém código de saída a partir da string
{
        unsigned long long      i; // Variável para armazenar resultado

        if (!arg) // Se nenhum argumento for passado
                return (g_last_exit_code); // Retorna último código de saída
        i = 0; // Índice de leitura
        while (ft_isspace(arg[i])) // Ignora espaços iniciais
                i++; // Avança
        if (arg[i] == '\0') // Se string estiver vazia após espaços
                *error = true; // Marca erro
        if (arg[i] == '-' || arg[i] == '+') // Se há sinal
                i++; // Avança
        if (!ft_isdigit(arg[i])) // Se caractere não for dígito
                *error = true; // Marca erro
        while (arg[i]) // Percorre o restante da string
        {
                if (!isdigit(arg[i]) && !ft_isspace(arg[i])) // Caracter inválido
                        *error = true; // Marca erro
                i++; // Avança
        }
        i = ft_atoi_long(arg, error); // Converte argumento para número
        return (i % 256); // Retorna código de saída limitado a 0-255
}

/* is_quiet_mode:
*       If exit is not called alone, it should not print "exit".
*       Returns true if exit should not be printed. False if exit was called
*       alone and the "exit" message should be printed.
*/
static bool     is_quiet_mode(t_data *data) // Verifica se deve suprimir mensagem "exit"
{
        t_command       *cmd; // Ponteiro para comando atual

        cmd = data->cmd; // Obtém comando atual
        if (!cmd) // Se não houver comando
                return (false); // Não é modo silencioso
        if (cmd->next != NULL || cmd->prev != NULL) // Se houver comandos encadeados
                return (true); // Suprime mensagem
        return (false); // Caso contrário, imprime mensagem
}

/* exit_builtin:
*       Executes the exit builtin.
*       If alone, prints exit and exits the shell with the provided exit code, or 0.
*       If piped, exits the child process with the provided exit code and does not exit
*       minishell.
*       In case of failure due to invalid arguments, does not exit the shell
*       and returns an error exit code (1 or 2) instead.
*/
int     exit_builtin(t_data *data, char **args) // Implementa o builtin exit
{
        int             exit_code; // Código de saída final
        bool            error; // Indica se houve erro ao interpretar argumento
        bool            quiet; // Indica se mensagem "exit" deve ser suprimida

        quiet = is_quiet_mode(data); // Determina se está em modo silencioso
        error = false; // Inicializa indicador de erro
        if (!quiet && data->interactive) // Se deve exibir mensagem e shell é interativo
                ft_putendl_fd("exit", 2); // Exibe mensagem "exit"
        if (!args || !args[1]) // Se não há argumentos numéricos
                exit_code = g_last_exit_code; // Usa último código de saída
        else // Caso tenha argumento
        {
                exit_code = get_exit_code(args[1], &error); // Converte argumento para número
                if (error) // Se número inválido
                        exit_code = errmsg_cmd("exit", args[1], // Imprime erro correspondente
                                        "numeric argument required", 2); // Mensagem e código 2
                else if (args[2]) // Se houver argumentos a mais
                        return (errmsg_cmd("exit", NULL, "too many arguments", 1)); // Retorna erro sem sair
        }
        exit_shell(data, exit_code); // Encerra o shell com código apropriado
        return (2); // Retorna 2 para indicar saída
}

