#include "../../minishell.h"

void    func_for_exit(t_mini *mini, char **command)
{
    mini->exit = 1;
    ft_putstr_fd("exit", STDERR);
    if (command[1] && command[2])
    {
        mini->ret = 1;
        ft_putendl_fd("minishell: exit: too many args", STDERR);
    }
}