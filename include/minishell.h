/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                            :+:      :+:    :+:   */
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
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrkhedr <amrkhedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 00:00:00 by amrkhedr          #+#    #+#             */
/*   Updated: 2026/03/30 00:00:00 by amrkhedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

char	*get_env_value(char **envp, const char *key);
char	*find_command_path(char *cmd, char **envp);
int		execute_builtin(char **args, char **envp);
char	**ft_simple_split(char *s);
void	execute_with_redirections(char **args, char **envp);
void	execute_pipeline(char *line, char **envp);
void	apply_redir_fd(char *file, int flags, int target_fd);
void	parse_and_apply_redirections(char **args);
void	execute_single_pipeline_cmd(char *cmd1_str, char **envp);
void	execute_full_pipeline(char *cmd1, char *cmd2, char **envp);

#endif
