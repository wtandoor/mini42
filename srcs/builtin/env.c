#include "../../minishell.h"

int     func_for_env(t_env *env)
{
    while (env)
    {
        ft_putendl(env->value);
        env = env->next;
    }
    return (SUCCESS);
}