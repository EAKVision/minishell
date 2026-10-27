/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                       :+:      :+:    :+:   */
/*                                                    :+:      :+:    :+:   */
/*   By: Amr Khedr (ELITE AKV) <amr.f.khedr@gmail.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 01:00:00 by akhedr            #+#    #+#             */
/*   Updated: 2026/10/28 01:00:00 by akhedr           ###   ########.fr       */
/*                                                                            */
/*   Copyright (c) 2026 Amr Khedr. All Rights Reserved.                      */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrkhedr <amrkhedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 00:00:00 by amrkhedr          #+#    #+#             */
/*   Updated: 2026/03/30 00:00:00 by amrkhedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_redir_fd(char *file, int flags, int target_fd)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd < 0)
	{
		perror("ak-shell: open");
		exit(1);
	}
	dup2(fd, target_fd);
	close(fd);
}

void	parse_and_apply_redirections(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (strcmp(args[i], ">") == 0 && args[i + 1])
			apply_redir_fd(args[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 1);
		else if (strcmp(args[i], ">>") == 0 && args[i + 1])
			apply_redir_fd(args[i + 1], O_CREAT | O_WRONLY | O_APPEND, 1);
		else if (strcmp(args[i], "<") == 0 && args[i + 1])
			apply_redir_fd(args[i + 1], O_RDONLY, 0);
		else
		{
			i++;
			continue ;
		}
		args[i] = NULL;
		break ;
	}
}

void	execute_single_pipeline_cmd(char *cmd1_str, char **envp)
{
	char	**args;
	pid_t	pid;

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
}

static void	setup_child_pipe(int *pipefd, int dup_idx,
								char *cmd, char **envp)
{
	dup2(pipefd[dup_idx], dup_idx);
	close(pipefd[0]);
	close(pipefd[1]);
	execute_with_redirections(ft_simple_split(cmd), envp);
}

void	execute_full_pipeline(char *cmd1, char *cmd2, char **envp)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipefd) < 0)
	{
		perror("ak-shell: pipe");
		return ;
	}
	pid1 = fork();
	if (pid1 == 0)
		setup_child_pipe(pipefd, 1, cmd1, envp);
	pid2 = fork();
	if (pid2 == 0)
		setup_child_pipe(pipefd, 0, cmd2, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
