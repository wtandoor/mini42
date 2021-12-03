#include "../minishell.h"
//discovering are_pipe (((box

int			box(char *path, char **arg, t_env *env, t_mini *mini)
{
    char **env_arr;
    char *p;
    int res;

    res = 0;
    g_sig.pid = fork();

}

void ft_close(int fd)
{
    if (fd > 0)
        close(fd);
}

char *check_dir(char *str, char *cmd)
{
    DIR *folder;
    struct dirent *item;
    char *path;

    path = NULL;
    folder = opendir(str);
    if (!folder)
        return (NULL);
    item = readdir(folder);
    while (item)
    {
        if (ft_strcmp(item->d_name, cmd) == 0)
			path = path_join(str, item->d_name);
        item = readdir(folder);
    }
    closedir(folder);
    return (path);
}

int error(char *path)
{
    DIR *folder;
    int fd;
    int res;
    fd = open(path, O_WRONLY);
    folder = opendir(path);
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(path, 2);
    if (ft_strchr(path, '/') == NULL)
        ft_putendl_fd(": command not found", 2);
    else if (fd == -1 && folder == NULL)
        ft_putendl_fd("No such file in directory", 2);
    else if (fd == -1 && folder != NULL)
        ft_putendl_fd("Is a directory", 2);
    else if (fd != -1 && folder == NULL)
        ft_putendl_fd("Permission denied", 2);
    if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
        res = 127;
    else
        res = 126;
    if (folder)
        closedir(folder);
    ft_close(fd);
    return (res);
}

char *join_path(char *str1, char *str2)
{
    char *temp;
    char *new;

    temp = ft_strjoin(str1, "/");
    new = ft_strjoin(temp, str2);
    delete_memmory(temp); 
    return (new);
}

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