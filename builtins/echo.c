#include "../minishell.h"

int num_args(char **args)
{
    int i;

    i = 0;
    while (args[i])
        i++;
    return (i);
}

int ft_echo(char **args)
{
    int i;
    int f;
    int n;

    n = 0;
    i = 1;
    f = num_args(args);
    if (f > 1)
    {
        while (args[i] && ft_strcmp(args[i], "-n") == 0)
        {
            n = 1;
            i++;
        }
        while (args[i])
        {
            if (args[i + 1] && n == 1)
                i++;
            ft_putstr_fd(args[i], 1);
            if (args[i + 1] && args[i][0] != '\0')
                write(1, " ", 1);
            i++;
        }
    }
    if (n == 0)
        write(1, "\n", 1);
    return (0);
}
