#include "../minishell.h"

int is_builtin_command(char *command)
{
    if (ft_strcmp(command, "cd") == 0)
        return (1);
    if (ft_strcmp(command, "pwd") == 0)
        return (1);
    if (ft_strcmp(command, "echo") == 0)
        return (1);
    if (ft_strcmp(command, "env") == 0)
        return (1);
    if (ft_strcmp(command, "export") == 0)
        return (1);
    if (ft_strcmp(command, "unset") == 0)
        return (1);
    return (0);
}

int execute_builtn(char **arg, t_mini *mini)
{
    int res;

    res = 0;
    if (ft_strcmp(arg[0], "cd") == 0)
        res = cd(arg);
    if (ft_strcmp(arg[0], "pwd") == 0)
        res = pwd(arg);
    if (ft_strcmp(arg[0], "echo") == 0)
        res = echo(arg);
    if (ft_strcmp(arg[0], "env") == 0)
        res = env(arg);
    if (ft_strcmp(arg[0], "export") == 0)
        res = export(arg);
    if (ft_strcmp(arg[0], "unset") == 0)
        res = unset(arg);
    return (res);
}