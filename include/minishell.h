#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

char	**ft_simple_split(char *s);
int		execute_builtin(char **args, char **envp);
char	*get_env_value(char **envp, const char *key);
char	*find_command_path(char *cmd, char **envp);
void	execute_with_redirections(char **args, char **envp);
void	execute_pipeline(char *line, char **envp);

#endif
