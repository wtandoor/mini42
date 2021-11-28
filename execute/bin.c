#include "../includes/minishell.h"
//discovering are_pipe execute_bin ft_close box

int execute_bin(char **arg, t_env *env, t_mini *mini)
{
    int i;
    char **bin;
    char *path;
    int res;

    i = 0;
    res = 127;
    while (env && env->value && ft_strncmp(env->value, "PATH", 5) != 0)
        env = env->next;
    if (env == NULL || env->next == NULL)
        return (box(arg[0], arg, env, mini));
    bin = ft_split(env->value, ':');
    if (!arg[0] && !bin[0])
        return (1);
    i = 1;
    path = check_dir(bin[0] + 5, arg[0]);
    if (path != NULL)
        res = box(path, arg, env, mini);
    else
        res = box(arg[0], arg, env, mini);
    free_arr2(bin);
    delete_memmory(path);
    return (res);
}

char **create_tab(t_token *token)
{
    t_token *token1;
    char **tab;
    int i;

    if (!token)
        return (NULL);
    token1 = token->next;
    i = 2;
    while(token1 && token1->type < 3)
    {
        token1 = token1->next;
        i++;
    }
    tab = malloc(sizeof(char *) * i);
    if (!tab)
        return (NULL);
    token1 = token->next;
    tab[0] = token->str;
    i = 1;
    while (token1 && token1->type < 3)
    {
        tab[i++] = token1->str;
        token1 = token1->next;
    }
    tab[i] = NULL;
    return (tab);
}

void execute_command(t_mini *mini, t_token *token)
{
    char    **command;
    int     i;

    if (mini->charge == 0)
        return ;
    i = 0;
    command = create_tab(token);
    while (command && command[i])
        command[i] = discovering(command[i++], mini->env, mini->ret);
    if (command && ft_strcmp(command[0], "exit") == 0 && are_pipe(token) == 0)
        mini_exit(mini, command);
    else if (command && is_builtin_command(command[0]))
        mini->ret = execute_builtin(command, mini);
    else if (command)
        mini->ret = execute_bin(command, mini->env, mini);
    free_arr2(command);
    ft_close(mini->pipin);
	ft_close(mini->pipout);
	mini->pipin = -1;
	mini->pipout = -1;
	mini->charge = 0;      
}