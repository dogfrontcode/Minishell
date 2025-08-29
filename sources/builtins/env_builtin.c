/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:55:54 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/19 15:41:22 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // Inclui definições do minishell

/* env_builtin:
*       Executes the builtin env command: Prints the environment variables.
*/
int     env_builtin(t_data *data, char **args) // Implementa comando env
{
        int     i; // Índice para percorrer o ambiente

        if (args && args[1]) // Verifica se existem argumentos extras
                return (errmsg_cmd("env", NULL, "too many arguments", 2)); // Erro por argumentos a mais
        i = 0; // Inicializa contador
        if (!data->env) // Se ambiente não existe
                return (EXIT_FAILURE); // Retorna falha
        while (data->env[i]) // Percorre todas as variáveis de ambiente
                ft_putendl_fd(data->env[i++], STDOUT_FILENO); // Imprime variável e avança
        return (EXIT_SUCCESS); // Retorna sucesso
}

