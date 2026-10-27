#include "minishell.h"

char	**ft_simple_split(char *s)
{
	char	**args;
	int		i;
	char	*token;

	args = malloc(sizeof(char *) * 64);
	if (!args)
		return (NULL);
	i = 0;
	token = strtok(s, " \t\n");
	while (token)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	return (args);
}

void	execute_with_redirections(char **args, char **envp)
{
	int		i;
	int		fd;
	char	*path;

	i = 0;
	while (args[i])
	{
		if (strcmp(args[i], ">") == 0 && args[i + 1])
		{
			fd = open(args[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("ak-shell: open");
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
			args[i] = NULL;
			break ;
		}
		else if (strcmp(args[i], ">>") == 0 && args[i + 1])
		{
			fd = open(args[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
			{
				perror("ak-shell: open");
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
			args[i] = NULL;
			break ;
		}
		else if (strcmp(args[i], "<") == 0 && args[i + 1])
		{
			fd = open(args[i + 1], O_RDONLY);
			if (fd < 0)
			{
				perror("ak-shell: open");
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
			args[i] = NULL;
			break ;
		}
		i++;
	}
	if (execute_builtin(args, envp))
		exit(0);
	path = find_command_path(args[0], envp);
	if (!path)
	{
		printf("ak-shell: command not found: %s\n", args[0]);
		exit(127);
	}
	execve(path, args, envp);
	perror("ak-shell: execve");
	exit(126);
}

void	execute_pipeline(char *line, char **envp)
{
	char	*cmd1_str;
	char	*cmd2_str;
	char	**args;
	pid_t	pid;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	cmd1_str = strtok(line, "|");
	cmd2_str = strtok(NULL, "|");
	if (!cmd2_str)
	{
		args = ft_simple_split(cmd1_str);
		if (args && args[0])
		{
			if (!execute_builtin(args, envp))
			{
				pid = fork();
				if (pid == 0)
					execute_with_redirections(args, envp);
				else
					waitpid(pid, NULL, 0);
			}
		}
		free(args);
		return ;
	}
	if (pipe(pipefd) < 0)
	{
		perror("ak-shell: pipe");
		return ;
	}
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_with_redirections(ft_simple_split(cmd1_str), envp);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_with_redirections(ft_simple_split(cmd2_str), envp);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
