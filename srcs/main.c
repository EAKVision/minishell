#include "minishell.h"

int execute_builtin(char **args, char **envp)
{
    if (!args[0])
        return (1);
    if (strcmp(args[0], "exit") == 0)
    {
        printf("exit\n");
        exit(0);
    }
    else if (strcmp(args[0], "pwd") == 0)
    {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            printf("%s\n", cwd);
        return (1);
    }
    else if (strcmp(args[0], "env") == 0)
    {
        int i = 0;
        while (envp && envp[i])
        {
            printf("%s\n", envp[i]);
            i++;
        }
        return (1);
    }
    return (0);
}

void execute_cmd(char **args, char **envp)
{
    pid_t pid;
    int status;
    char full_path[512];

    if (execute_builtin(args, envp))
        return;

    pid = fork();
    if (pid < 0)
    {
        perror("ak-shell: fork failed");
        return;
    }
    if (pid == 0)
    {
        if (execve(args[0], args, envp) == -1)
        {
            snprintf(full_path, sizeof(full_path), "/bin/%s", args[0]);
            if (execve(full_path, args, envp) == -1)
            {
                snprintf(full_path, sizeof(full_path), "/usr/bin/%s", args[0]);
                if (execve(full_path, args, envp) == -1)
                {
                    fprintf(stderr, "ak-shell: command not found: %s\n", args[0]);
                    exit(127);
                }
            }
        }
    }
    else
    {
        waitpid(pid, &status, 0);
    }
}

char **split_args(char *line)
{
    int bufsize = 64, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "ak-shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n\v");
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "ak-shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " \t\r\n\v");
    }
    tokens[position] = NULL;
    return (tokens);
}

int main(int argc, char **argv, char **envp)
{
    char *line;
    char **args;

    (void)argc;
    (void)argv;
    printf("🔥 Elite AK Vision Minishell Initialized 🔥\n");
    while (1)
    {
        line = readline("ak-shell$ ");
        if (!line)
        {
            printf("exit\n");
            break;
        }
        if (*line)
        {
            add_history(line);
            args = split_args(line);
            if (args[0])
                execute_cmd(args, envp);
            free(args);
        }
        free(line);
    }
    return (0);
}
