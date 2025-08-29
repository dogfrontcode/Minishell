/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:30:41 by mcombeau          #+#    #+#             */
/*   Updated: 2022/11/05 12:17:12 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // Inclui definições do minishell

/* get_key_value_pair:
*       Separates the given argument into a key-value pair
*       for the environment variable.
*       Returns an array of 2 strings containing the key and the
*       value of the new environment variable.
*       Returns NULL in case of error.
*/
static char     **get_key_value_pair(char *arg) // Divide argumento em chave e valor
{
        char    **tmp; // Armazena par chave/valor
        char    *eq_pos; // Posição do caractere '='

        eq_pos = ft_strchr(arg, '='); // Encontra '=' no argumento
        tmp = malloc(sizeof * tmp * (2 + 1)); // Aloca espaço para duas strings e NULL
        tmp[0] = ft_substr(arg, 0, eq_pos - arg); // Extrai a chave
        tmp[1] = ft_substr(eq_pos, 1, ft_strlen(eq_pos)); // Extrai o valor
        tmp[2] = NULL; // Finaliza array com NULL
        return (tmp); // Retorna par chave/valor
}

/* export_builtin:
*       Adds the given variables to the environment variables.
*       Returns 0 if all args were successfully added to env,
*       or 1 if one or more args were not added to env.
*/
int     export_builtin(t_data *data, char **args) // Implementa comando export
{
        int     i; // Índice dos argumentos
        char    **tmp; // Par chave/valor temporário
        int     ret; // Código de retorno

        ret = EXIT_SUCCESS; // Assume sucesso inicial
        i = 1; // Começa após nome do comando
        if (!args[i]) // Se não houver argumentos
                return (env_builtin(data, NULL)); // Exibe variáveis de ambiente
        while (args[i]) // Percorre todos os argumentos
        {
                if (!is_valid_env_var_key(args[i])) // Verifica se chave é válida
                {
                        errmsg_cmd("export", args[i], "not a valid identifier", false); // Mensagem de erro
                        ret = EXIT_FAILURE; // Marca falha
                }
                else if (ft_strchr(args[i], '=') != NULL) // Se argumento contém '='
                {
                        tmp = get_key_value_pair(args[i]); // Separa chave e valor
                        set_env_var(data, tmp[0], tmp[1]); // Define variável de ambiente
                        free_str_tab(tmp); // Libera memória temporária
                }
                i++; // Próximo argumento
        }
        return (ret); // Retorna status final
}

