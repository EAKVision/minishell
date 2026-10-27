#include "minishell.h"

int	execute_builtin(char **args, char **envp)
{
	int		i;
	char	cwd[1024];
	char	*home;

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
	{
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
	else if (strcmp(args[0], "env") == 0)
	{
		i = 0;
		while (envp && envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
		return (1);
	}
	return (0);
}
