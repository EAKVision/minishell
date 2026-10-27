/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                             :+:      :+:    :+:   */
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
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrkhedr <amrkhedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 00:00:00 by amrkhedr          #+#    #+#             */
/*   Updated: 2026/03/30 00:00:00 by amrkhedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_simple_split(char *s)
{
	char	**res;

	res = malloc(sizeof(char *) * 2);
	if (!res)
		return (NULL);
	res[0] = s;
	res[1] = NULL;
	return (res);
}

void	execute_with_redirections(char **args, char **envp)
{
	char	*path;

	parse_and_apply_redirections(args);
	if (!args || !args[0])
		exit(0);
	if (execute_builtin(args, envp))
		exit(0);
	path = find_command_path(args[0], envp);
	if (!path)
	{
		write(2, "ak-shell: command not found: ", 29);
		write(2, args[0], strlen(args[0]));
		write(2, "\n", 1);
		exit(127);
	}
	execve(path, args, envp);
	perror("ak-shell: execve");
	exit(1);
}

void	execute_pipeline(char *line, char **envp)
{
	char	*pipe_pos;

	pipe_pos = strchr(line, '|');
	if (pipe_pos)
	{
		*pipe_pos = '\0';
		execute_full_pipeline(line, pipe_pos + 1, envp);
	}
	else
		execute_single_pipeline_cmd(line, envp);
}
