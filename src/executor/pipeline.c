#include "../../includes/minishell.h"

extern char **environ;
extern int  g_last_exit_status;

int	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strncmp(cmd_name, "echo", 4) == 0 && ft_strlen(cmd_name) == 4)
		return (1);
	if (ft_strncmp(cmd_name, "pwd", 3) == 0 && ft_strlen(cmd_name) == 3)
		return (1);
	if (ft_strncmp(cmd_name, "env", 3) == 0 && ft_strlen(cmd_name) == 3)
		return (1);
	if (ft_strncmp(cmd_name, "exit", 4) == 0 && ft_strlen(cmd_name) == 4)
		return (1);
	if (ft_strncmp(cmd_name, "cd", 2) == 0 && ft_strlen(cmd_name) == 2)
		return (1);
	if (ft_strncmp(cmd_name, "export", 6) == 0 && ft_strlen(cmd_name) == 6)
		return (1);
	if (ft_strncmp(cmd_name, "unset", 5) == 0 && ft_strlen(cmd_name) == 5)
		return (1);
	return (0);
}

static void	execute_echo(char **args, int arg_count)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (arg_count > 1 && ft_strncmp(args[1], "-n", 2) == 0 
		&& ft_strlen(args[1]) == 2)
	{
		newline = 0;
		i = 2;
	}
       while (i < arg_count)
       {
               if (ft_strncmp(args[i], "$?", 2) == 0 && ft_strlen(args[i]) == 2)
                       printf("%d", g_last_exit_status);
               else
                       printf("%s", args[i]);
               if (i < arg_count - 1)
                       printf(" ");
               i++;
       }
	if (newline)
		printf("\n");
}

static void	execute_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	else
		printf("pwd: error getting current directory\n");
}

static void	execute_env(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

static int	execute_cd(char **args, int arg_count)
{
	char	*path;
	char	*home;

	if (arg_count > 2)
	{
		fprintf(stderr, "minishell: cd: too many arguments\n");
		return (1);
	}
	
	if (arg_count == 1)
	{
		home = getenv("HOME");
		if (!home)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (1);
		}
		path = home;
	}
	else
		path = args[1];
	
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

// Função para validar nomes de variáveis
static int	is_valid_identifier(const char *name)
{
	int i;

	if (!name || !*name)
		return (0);
	
	// Primeiro caractere deve ser letra ou underscore
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	
	// Resto deve ser alfanumérico ou underscore
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	execute_export(char **args, int arg_count)
{
	char	*equal_sign;
	char	*name;
	char	*value;
	int		i;
	int		exit_code = 0;

	if (arg_count == 1)
	{
		// Sem argumentos, mostra todas as variáveis exportadas
		execute_env();
		return (0);
	}
	
	i = 1;
	while (i < arg_count)
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
		{
			// Formato: VAR=value
			name = ft_substr(args[i], 0, equal_sign - args[i]);
			value = equal_sign + 1;
			
			if (!name || !is_valid_identifier(name))
			{
				fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", args[i]);
				exit_code = 1;
				if (name)
					free(name);
			}
			else
			{
				if (setenv(name, value, 1) == -1)
				{
					perror("export");
					exit_code = 1;
				}
				free(name);
			}
		}
		else
		{
			// Formato: VAR (sem valor, apenas marca como exportada)
			if (!is_valid_identifier(args[i]))
			{
				fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", args[i]);
				exit_code = 1;
			}
			else
			{
				if (setenv(args[i], "", 1) == -1)
				{
					perror("export");
					exit_code = 1;
				}
			}
		}
		i++;
	}
	return (exit_code);
}

static int	execute_unset(char **args, int arg_count)
{
	int	i;
	int	exit_code = 0;

	if (arg_count == 1)
		return (0); // Sem argumentos, não faz nada
	
	i = 1;
	while (i < arg_count)
	{
		if (!is_valid_identifier(args[i]))
		{
			fprintf(stderr, "minishell: unset: `%s': not a valid identifier\n", args[i]);
			exit_code = 1;
		}
		else
		{
			if (unsetenv(args[i]) == -1)
			{
				perror("unset");
				exit_code = 1;
			}
		}
		i++;
	}
	return (exit_code);
}

// Função para verificar se uma string é numérica
static int	is_numeric(const char *str)
{
	int i = 0;
	
	if (!str || !*str)
		return (0);
	
	// Permite + ou - no início
	if (str[i] == '+' || str[i] == '-')
		i++;
	
	// Deve ter pelo menos um dígito após o sinal (se houver)
	if (!str[i])
		return (0);
	
	// Verifica se o resto são dígitos
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	execute_exit(char **args, int arg_count)
{
	int exit_code = 0;
	
	if (arg_count > 2)
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
		return (1);
	}
	
	if (arg_count == 2)
	{
		if (!is_numeric(args[1]))
		{
			fprintf(stderr, "minishell: exit: %s: numeric argument required\n", args[1]);
			exit(2);
		}
		exit_code = ft_atoi(args[1]);
		// Aplica modulo 256 para obter valor entre 0-255
		exit_code = ((exit_code % 256) + 256) % 256;
	}
	
	exit(exit_code);
	return (0); // Nunca será executado
}

int	execute_builtin(Command *cmd)
{
	if (!cmd->args || cmd->arg_count == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0 
		&& ft_strlen(cmd->args[0]) == 4)
	{
		execute_echo(cmd->args, cmd->arg_count);
		return (0);
	}
	else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0 
		&& ft_strlen(cmd->args[0]) == 3)
	{
		execute_pwd();
		return (0);
	}
	else if (ft_strncmp(cmd->args[0], "env", 3) == 0 
		&& ft_strlen(cmd->args[0]) == 3)
	{
		execute_env();
		return (0);
	}
	else if (ft_strncmp(cmd->args[0], "cd", 2) == 0 
		&& ft_strlen(cmd->args[0]) == 2)
		return (execute_cd(cmd->args, cmd->arg_count));
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0 
		&& ft_strlen(cmd->args[0]) == 6)
		return (execute_export(cmd->args, cmd->arg_count));
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0 
		&& ft_strlen(cmd->args[0]) == 5)
		return (execute_unset(cmd->args, cmd->arg_count));
	else if (ft_strncmp(cmd->args[0], "exit", 4) == 0 
		&& ft_strlen(cmd->args[0]) == 4)
		return (execute_exit(cmd->args, cmd->arg_count));
	else
		return (1);
}

static char     *get_command_path(char *cmd_name)
{
       char    *path_env;
       char    **dirs;
       char    *tmp;
       char    *full;
       int             i;

       if (ft_strchr(cmd_name, '/'))
               return (ft_strdup(cmd_name));
       path_env = getenv("PATH");
       if (!path_env)
               return (ft_strdup(cmd_name));
       dirs = ft_split(path_env, ':');
       if (!dirs)
               return (ft_strdup(cmd_name));
       i = 0;
       while (dirs[i])
       {
               tmp = ft_strjoin(dirs[i], "/");
               if (!tmp)
                       break ;
               full = ft_strjoin(tmp, cmd_name);
               free(tmp);
               if (!full)
                       break ;
               if (access(full, X_OK) == 0)
               {
                       int j = 0;
                       while (dirs[j])
                               free(dirs[j++]);
                       free(dirs);
                       return (full);
               }
               free(full);
               i++;
       }
       i = 0;
       while (dirs[i])
               free(dirs[i++]);
       free(dirs);
       return (ft_strdup(cmd_name));
}


int     execute_single_command(Command *cmd)
{
	pid_t	pid;
	int		status;
	char	*path;

       if (!cmd->args || cmd->arg_count == 0)
               return (1);
       if (cmd->redir_count == 0 && is_builtin(cmd->args[0]))
       {
               g_last_exit_status = execute_builtin(cmd);
               return (g_last_exit_status);
       }
	pid = fork();
	if (pid == 0)
	{
		restore_signals();
		if (setup_redirections(cmd))
			exit(1);
		if (is_builtin(cmd->args[0]))
		{
			execute_builtin(cmd);
			exit(0);
		}
		path = get_command_path(cmd->args[0]);
		execve(path, cmd->args, environ);
		perror("execve");
		exit(127);
	}
       else if (pid > 0)
       {
               waitpid(pid, &status, 0);
               g_last_exit_status =
                       (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
               return (g_last_exit_status);
       }
	else
	{
		perror("fork");
		return (1);
	}
}

static int	**create_pipes(int cmd_count)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * (cmd_count - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

static void	setup_child_pipes(int **pipes, int cmd_count, int i)
{
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < cmd_count - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
}

static void	close_all_pipes(int **pipes, int cmd_count)
{
	int	j;

	j = 0;
	while (j < cmd_count - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

static void	execute_child_command(Command *cmd, int **pipes, int cmd_count, int i)
{
	char	*path;

	restore_signals();
	setup_child_pipes(pipes, cmd_count, i);
	if (setup_redirections(cmd))
		exit(1);
	close_all_pipes(pipes, cmd_count);
	if (is_builtin(cmd->args[0]))
	{
		execute_builtin(cmd);
		exit(0);
	}
	else
	{
		path = get_command_path(cmd->args[0]);
		execve(path, cmd->args, environ);
		perror("execve");
		exit(127);
	}
}

static pid_t	*create_child_processes(Command *commands, int cmd_count, 
	int **pipes)
{
	pid_t	*pids;
	int		i;

	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		return (NULL);
	i = 0;
	while (i < cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			execute_child_command(&commands[i], pipes, cmd_count, i);
		i++;
	}
	return (pids);
}

static void	cleanup_pipes(int **pipes, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
}

static int	wait_all_processes(pid_t *pids, int cmd_count)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
       while (i < cmd_count)
       {
               waitpid(pids[i], &status, 0);
               i++;
       }
       g_last_exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
       return (g_last_exit_status);
}

int	execute_pipeline(Command *commands, int cmd_count)
{
	int		**pipes;
	pid_t	*pids;
	int		status;

	if (cmd_count == 1)
		return (execute_single_command(&commands[0]));
	pipes = create_pipes(cmd_count);
	if (!pipes)
		return (1);
	pids = create_child_processes(commands, cmd_count, pipes);
	if (!pids)
		return (1);
	cleanup_pipes(pipes, cmd_count);
	status = wait_all_processes(pids, cmd_count);
	free(pipes);
	free(pids);
	return (status);
} 