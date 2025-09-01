/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 19:03:08 by mcombeau          #+#    #+#             */
/*   Updated: 2022/11/11 14:22:23 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // Inclui definições necessárias para o minishell

/* update_wds:
*       Updates the PWD and OLDPWD in the environment after a directory change.
*       A copy of the paths are stored internally for use in case the environment
*       variables are unset.
*/
static void     update_wds(t_data *data, char *wd) // Atualiza variáveis PWD e OLDPWD
{
        set_env_var(data, "OLDPWD", get_env_var_value(data->env, "PWD")); // Define OLDPWD com valor atual de PWD
        set_env_var(data, "PWD", wd); // Define PWD com novo diretório
        if (data->old_working_dir) // Se diretório antigo está armazenado
        {
                free_ptr(data->old_working_dir); // Libera memória do diretório antigo
                data->old_working_dir = ft_strdup(data->working_dir); // Salva working_dir atual em old_working_dir
        } // Fim do bloco old_working_dir
        if (data->working_dir) // Se diretório atual está armazenado
        {
                free_ptr(data->working_dir); // Libera memória do working_dir atual
                data->working_dir = ft_strdup(wd); // Atualiza working_dir com novo caminho
        } // Fim do bloco working_dir
        free_ptr(wd); // Libera memória de wd
} // Fim da função update_wds

/* chdir_errno_mod:
*       chdir can sometimes set errno to ESTALE ("Stale file handle")
*       when a parent directory is removed on some systems. This is due
*       to the inode table entry being recycled. This is a fix to display
*       "no such file or directory" error instead.
*/
static bool     chdir_errno_mod(char *path) // Ajusta errno específico e exibe erro
{
        if (errno == ESTALE) // Verifica se errno é ESTALE
                errno = ENOENT; // Converte para ENOENT
        errmsg_cmd("cd", path, strerror(errno), errno); // Exibe mensagem de erro do cd
        return (false); // Retorna falso indicando falha
} // Fim de chdir_errno_mod

/* change_dir:
*       Changes the current working directory and updates the
*       OLDPWD environment variable.
*       Returns 1 on success, 0 on failure.
*/
static bool     change_dir(t_data *data, char *path) // Muda diretório de trabalho
{
        char    *ret; // Caminho resultado
        char    *tmp; // Ponteiro temporário
        char    cwd[PATH_MAX]; // Buffer para getcwd

        ret = NULL; // Inicializa ret
        if (chdir(path) != 0) // Tenta alterar diretório
                return (chdir_errno_mod(path)); // Trata erro e retorna falso
        ret = getcwd(cwd, PATH_MAX); // Obtém diretório atual
        if (!ret) // Se getcwd falhar
        {
                errmsg_cmd("cd: error retrieving current directory", // Mensagem de erro
                        "getcwd: cannot access parent directories", // Detalhe do erro
                        strerror(errno), errno); // Código e descrição
                ret = ft_strjoin(data->working_dir, "/"); // Concatena working_dir e '/'
                tmp = ret; // Guarda ponteiro para liberar
                ret = ft_strjoin(tmp, path); // Concatena com path
                free_ptr(tmp); // Libera temporário
        }
        else // Se getcwd bem-sucedido
                ret = ft_strdup(cwd); // Duplica caminho obtido
        update_wds(data, ret); // Atualiza variáveis de diretório
        return (true); // Sucesso
} // Fim da função change_dir

/* cd_builtin:
*       Executes the builtin cd command by changing the working directory.
*       Returns 0 on success, 1 on failure.
*/
int     cd_builtin(t_data *data, char **args) // Executa comando cd
{
        char    *path; // Caminho alvo

        if (!args || !args[1] || ft_isspace(args[1][0]) // Sem argumento válido
                || args[1][0] == '\0' || ft_strncmp(args[1], "--", 3) == 0) // Argumento vazio ou '--'
        {
                path = get_env_var_value(data->env, "HOME"); // Obtém HOME
                if (!path || *path == '\0' || ft_isspace(*path)) // Verifica se HOME definido
                        return (errmsg_cmd("cd", NULL, "HOME not set", EXIT_FAILURE)); // Erro se não definido
                return (!change_dir(data, path)); // Muda para HOME
        }
        if (args[2]) // Se há argumentos extras
                return (errmsg_cmd("cd", NULL, "too many arguments", EXIT_FAILURE)); // Erro por muitos argumentos
        if (ft_strncmp(args[1], "-", 2) == 0) // Se argumento é '-'
        {
                path = get_env_var_value(data->env, "OLDPWD"); // Obtém OLDPWD
                if (!path) // Se OLDPWD não definido
                        return (errmsg_cmd("cd", NULL, "OLDPWD not set", EXIT_FAILURE)); // Erro
                return (!change_dir(data, path)); // Muda para OLDPWD
        }
        return (!change_dir(data, args[1])); // Muda para caminho fornecido
} // Fim de cd_builtin

