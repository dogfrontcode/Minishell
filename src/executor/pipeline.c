#include "../../includes/minishell.h"

extern char **environ;

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

int	execute_builtin(Command *cmd)
{
	if (!cmd->args || cmd->arg_count == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0 
		&& ft_strlen(cmd->args[0]) == 4)
		execute_echo(cmd->args, cmd->arg_count);
	else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0 
		&& ft_strlen(cmd->args[0]) == 3)
		execute_pwd();
	else if (ft_strncmp(cmd->args[0], "env", 3) == 0 
		&& ft_strlen(cmd->args[0]) == 3)
		execute_env();
	else if (ft_strncmp(cmd->args[0], "exit", 4) == 0 
		&& ft_strlen(cmd->args[0]) == 4)
		exit(0);
	else
		return (1);
	return (0);
}

static char	*get_command_path(char *cmd_name)
{
	char	*path;

	if (ft_strchr(cmd_name, '/'))
		return (cmd_name);
	path = malloc(ft_strlen(cmd_name) + 6);
	if (!path)
		return (NULL);
	ft_strlcpy(path, "/bin/", 6);
	ft_strlcat(path, cmd_name, ft_strlen(cmd_name) + 6);
	return (path);
}

static int	execute_external(Command *cmd)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = get_command_path(cmd->args[0]);
	if (!path)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		restore_signals();
		execve(path, cmd->args, environ);
		perror("execve");
		exit(127);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (path != cmd->args[0])
			free(path);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
	else
	{
		perror("fork");
		if (path != cmd->args[0])
			free(path);
		return (1);
	}
}

int	execute_single_command(Command *cmd)
{
	if (!cmd->args || cmd->arg_count == 0)
		return (1);
	if (is_builtin(cmd->args[0]))
		return (execute_builtin(cmd));
	return (execute_external(cmd));
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
	return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
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