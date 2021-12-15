#include "../minishell.h"

int not_valid_str(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!(str[i] >= 0 && str[i] < 10))
            return (1);
        i++;
    }
    return (0);
}

void	skip_space_nl(const char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n')
	|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}

int get_lvl(char *str)
{
    int i;
    int sign;
    int n;

    i = 0;
    sign = 1;
    n = 0;
    skip_space_nl(str, &i);
    if (not_valid_str(str))
        return (0);
    if (str[i] == '-')
        sign = -1;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i] >= 0 && str[i] < 10)
        n = n * 10 + (str[i++] - '0');
    return (n * sign);
}

void    update_shell_lvl(t_env *env)
{
    int lvl;
    char env_name[4096];
    char *shlvl;
    char *shlvl_val;

    
    shlvl_val = get_env_val("SHLVL", env);
    if (ft_strcmp(shlvl_val, "") == 0)
        return;
    lvl = get_lvl(shlvl_val) + 1;
    delete_memmory(shlvl_val);
    while (env && env->next)
    {
        
        get_name(env_name, env->value);
        if (ft_strcmp("SHLVL", env_name) == 0)
        {
            delete_memmory(env->value);
            shlvl = ft_itoa(lvl);
            env->value = ft_strjoin("SHLVL=", shlvl);
            delete_memmory(shlvl);
            return ;
        }
        env = env->next;
    }
}