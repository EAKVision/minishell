/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                                 :+:      :+:    :+:   */
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
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrkhedr <amrkhedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 00:00:00 by amrkhedr          #+#    #+#             */
/*   Updated: 2026/03/30 00:00:00 by amrkhedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline("ak-shell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
		{
			add_history(line);
			execute_pipeline(line, envp);
		}
		free(line);
	}
	return (0);
}
