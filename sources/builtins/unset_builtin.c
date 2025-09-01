/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:29:52 by mcombeau          #+#    #+#             */
/*   Updated: 2022/11/05 12:17:21 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // Inclui definições do minishell

/* unset_builtin:
*       Removes the environment variables with the given keys
*       after checking if they are valid keys.
*       Does nothing if the key is not in the environment.
*       Returns 0 if all args were successfully unset, or 1 if
*       one or more args could not be unset.
*/
int     unset_builtin(t_data *data, char **args) // Implementa comando unset
{
        int     i; // Índice dos argumentos
        int     idx; // Índice da variável no ambiente
        int     ret; // Código de retorno

        ret = EXIT_SUCCESS; // Assume sucesso inicial
        i = 1; // Começa após nome do comando
        while (args[i]) // Percorre todos os argumentos
        {
                if (!is_valid_env_var_key(args[i]) || ft_strchr(args[i], '=') != NULL) // Verifica validade da chave
                {
                        errmsg_cmd("unset", args[i], "not a valid identifier", false); // Exibe erro de identificador
                        ret = EXIT_FAILURE; // Marca falha
                }
                else // Se chave é válida
                {
                        idx = get_env_var_index(data->env, args[i]); // Obtém índice da variável
                        if (idx != -1) // Se variável encontrada
                                remove_env_var(data, idx); // Remove variável do ambiente
                }
                i++; // Próximo argumento
        }
        return (ret); // Retorna status final
}

