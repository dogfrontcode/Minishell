/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:30:28 by mcombeau          #+#    #+#             */
/*   Updated: 2022/11/05 12:17:15 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // Inclui definições do minishell

/* pwd_builtin:
*       Executes the builtin pwd command and displays the
*       current working directory path.
*       Returns 0 if successful, 1 if an error occured.
*/
int     pwd_builtin(t_data *data, char **args) // Implementa comando pwd
{
        char    buf[PATH_MAX]; // Buffer para armazenar caminho
        char    *cwd; // Ponteiro para diretório atual

        (void)args; // Argumentos não utilizados
        if (data->working_dir) // Se diretório de trabalho já é conhecido
        {
                ft_putendl_fd(data->working_dir, STDOUT_FILENO); // Imprime diretório armazenado
                return (EXIT_SUCCESS); // Retorna sucesso
        }
        cwd = getcwd(buf, PATH_MAX); // Obtém diretório atual
        if (cwd) // Se getcwd foi bem-sucedido
        {
                ft_putendl_fd(cwd, STDOUT_FILENO); // Imprime caminho atual
                return (EXIT_SUCCESS); // Retorna sucesso
        }
        errmsg_cmd("pwd", NULL, strerror(errno), errno); // Exibe mensagem de erro
        return (EXIT_FAILURE); // Retorna falha
}

