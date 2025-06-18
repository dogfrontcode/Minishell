#include "../../includes/minishell.h"

extern char **environ;

// Função para verificar se é um built-in
int is_builtin(char *cmd_name)
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

// Função para executar built-in (movida do input.c)
static void execute_echo(char **args, int arg_count)
{
	int i = 1;
	int newline = 1;

	if (arg_count > 1 && ft_strncmp(args[1], "-n", 2) == 0 && ft_strlen(args[1]) == 2)
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

static void execute_pwd(void)
{
	char *cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	else
		printf("pwd: error getting current directory\n");
}

static void execute_env(void)
{
	extern char **environ;
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

// Executa comando built-in
int execute_builtin(Command *cmd)
{
	if (!cmd->args || cmd->arg_count == 0)
		return (1);

	if (ft_strncmp(cmd->args[0], "echo", 4) == 0 && ft_strlen(cmd->args[0]) == 4)
		execute_echo(cmd->args, cmd->arg_count);
	else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0 && ft_strlen(cmd->args[0]) == 3)
		execute_pwd();
	else if (ft_strncmp(cmd->args[0], "env", 3) == 0 && ft_strlen(cmd->args[0]) == 3)
		execute_env();
	else if (ft_strncmp(cmd->args[0], "exit", 4) == 0 && ft_strlen(cmd->args[0]) == 4)
		exit(0);
	else
		return (1); // Não é built-in

	return (0); // Sucesso
}

// Executa comando externo
static int execute_external(Command *cmd)
{
	pid_t pid;
	int status;
	char *path;

	// Monta path completo se necessário
	if (ft_strchr(cmd->args[0], '/'))
		path = cmd->args[0];
	else
	{
		// Para simplificar, vamos procurar em /bin
		path = malloc(ft_strlen(cmd->args[0]) + 6);
		if (!path)
			return (1);
		ft_strlcpy(path, "/bin/", 6);
		ft_strlcat(path, cmd->args[0], ft_strlen(cmd->args[0]) + 6);
	}

	pid = fork();
	if (pid == 0)
	{
		// Processo filho
		restore_signals();
		execve(path, cmd->args, environ);
		// Se chegou aqui, o execve falhou (não deveria acontecer se parser validou)
		perror("execve");
		exit(127);
	}
	else if (pid > 0)
	{
		// Processo pai
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

// Executa comando único
int execute_single_command(Command *cmd)
{
	if (!cmd->args || cmd->arg_count == 0)
		return (1);

	// Verifica se é built-in
	if (is_builtin(cmd->args[0]))
		return (execute_builtin(cmd));

	// Executa comando externo
	return (execute_external(cmd));
}

// Executa pipeline com múltiplos comandos
int execute_pipeline(Command *commands, int cmd_count)
{
	int **pipes;
	pid_t *pids;
	int i, j;
	int status = 0;

	if (cmd_count == 1)
		return (execute_single_command(&commands[0]));

	// Aloca arrays para pipes e PIDs
	pipes = malloc(sizeof(int *) * (cmd_count - 1));
	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pipes || !pids)
		return (1);

	// Cria pipes
	for (i = 0; i < cmd_count - 1; i++)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			return (1);
		}
	}

	// Executa cada comando da pipeline
	for (i = 0; i < cmd_count; i++)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			// Processo filho
			restore_signals();

			// Conecta entrada (stdin)
			if (i > 0)
			{
				dup2(pipes[i - 1][0], STDIN_FILENO);
			}

			// Conecta saída (stdout)
			if (i < cmd_count - 1)
			{
				dup2(pipes[i][1], STDOUT_FILENO);
			}

			// Fecha todos os pipes
			for (j = 0; j < cmd_count - 1; j++)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
			}

			// Executa comando
			if (is_builtin(commands[i].args[0]))
			{
				execute_builtin(&commands[i]);
				exit(0);
			}
			else
			{
				// Comando externo
				char *path;
				if (ft_strchr(commands[i].args[0], '/'))
					path = commands[i].args[0];
				else
				{
					path = malloc(ft_strlen(commands[i].args[0]) + 6);
					ft_strlcpy(path, "/bin/", 6);
					ft_strlcat(path, commands[i].args[0], ft_strlen(commands[i].args[0]) + 6);
				}
				
				execve(path, commands[i].args, environ);
				// Se chegou aqui, o execve falhou (não deveria acontecer se parser validou)
				perror("execve");
				exit(127);
			}
		}
	}

	// Processo pai: fecha pipes e espera filhos
	for (i = 0; i < cmd_count - 1; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
	}

	// Espera todos os processos filhos
	for (i = 0; i < cmd_count; i++)
	{
		waitpid(pids[i], &status, 0);
	}

	free(pipes);
	free(pids);

	return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
} 