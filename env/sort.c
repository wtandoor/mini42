#include "../minishell.h"

int str_env_length(char **env)
{
    int i;

    i = 0;
    while (env[i])
        i++;
    return (i);
}

size_t get_env_size(t_env *lst)
{
    size_t len;

    len = 0;
    while (lst && lst->next != NULL)
    {
        if (lst->value != NULL)
        {
            len = len + ft_strlen(lst->value);
            len++;
        }
        lst = lst->next;
    }
    return (len);
}

char    *env_str(t_env *lst)
{
    char *env;
    int i;
    int j;

    i = 0;
    env = malloc(sizeof(char) * get_env_size(lst) + 1);
    if (!env)
        return (NULL);
    while (lst && lst->next != NULL)
    {
        if (lst->value != NULL)
        {
            j = 0;
            while (lst->value[j])
                env[i++] = lst->value[j++];
        }
        if (lst->next->next != NULL)
            env[i++] = '\n';
        lst = lst->next;
    }
    env[i] = '\0';
    return (env);
}

void print_new_env(t_env *env)
{
    int i;
    char **arr;
    char *str_env;

    str_env = env_str(env);
    arr = ft_split(str_env, '\n');
    delete_memmory(str_env);
    sort(arr, str_env_length(arr));
    i = 0;
    while (arr[i])
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putendl_fd(arr[i], 1);
        i++;
    }
    free_arr2(arr);
}

void    sort(char **arr, int env_length)
{
    int j;
    int i;
    char *temp;

    j = 0;
    while (arr && j == 0)
    {
        j = 1;
        i = 0;
        while (i < env_length - 1)
        {
            if (ft_strcmp(arr[i], arr[i + 1] > 0))
            {
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                j = 0;
            }
            i++;
        }
        env_length--;
    }
}