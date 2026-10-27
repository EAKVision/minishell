/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                             :+:      :+:    :+:   */
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
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrkhedr <amrkhedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 00:00:00 by amrkhedr          #+#    #+#             */
/*   Updated: 2026/03/30 00:00:00 by amrkhedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_cd(char **args)
{
	char	*home;

	if (!args[1] || strcmp(args[1], "~") == 0)
	{
		home = getenv("HOME");
		if (home && chdir(home) != 0)
			perror("ak-shell: cd");
	}
	else if (chdir(args[1]) != 0)
		perror("ak-shell: cd");
	return (1);
}

static int	exec_env(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (1);
}

int	execute_builtin(char **args, char **envp)
{
	char	cwd[1024];

	if (!args[0])
		return (1);
	if (strcmp(args[0], "exit") == 0)
	{
		printf("exit\n");
		exit(0);
	}
	else if (strcmp(args[0], "pwd") == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("%s\n", cwd);
		return (1);
	}
	else if (strcmp(args[0], "cd") == 0)
		return (exec_cd(args));
	else if (strcmp(args[0], "env") == 0)
		return (exec_env(envp));
	return (0);
}
