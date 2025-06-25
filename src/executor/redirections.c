#include "../../includes/minishell.h"

static int	handle_heredoc(char *delimiter)
{
	char	*line;
	int		fd;
	char	template[] = "/tmp/minishell_hdXXXXXX";

	fd = mkstemp(template);
	if (fd == -1)
		return (-1);
	unlink(template);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	lseek(fd, 0, SEEK_SET);
	return (fd);
}

int	setup_redirections(Command *cmd)
{
	int	i;
	int		fd;

	i = 0;
	while (i < cmd->redir_count)
	{
		fd = -1;
		if (cmd->redirs[i].type == IN)
			fd = open(cmd->redirs[i].filename, O_RDONLY);
		else if (cmd->redirs[i].type == OUT)
			fd = open(cmd->redirs[i].filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (cmd->redirs[i].type == APPEND_OUT)
			fd = open(cmd->redirs[i].filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (cmd->redirs[i].type == HEREDOC_TYPE)
			fd = handle_heredoc(cmd->redirs[i].filename);
		if (fd == -1)
		{
			perror(cmd->redirs[i].filename);
			return (1);
		}
		if (cmd->redirs[i].type == IN || cmd->redirs[i].type == HEREDOC_TYPE)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		i++;
	}
	return (0);
}
