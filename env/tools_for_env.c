#include "../minishell.h"

void free_arr2(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        if (arr[i])
            delete_memmory(arr[i]);
        i++;
    }
    if (arr)
        delete_memmory(arr);
}

char *env_val1(char *env)
{
    int i;
    int j;
    char *env_val;
    int size;

    size = len_env_value(env) + 1;
    env_val = (char *)malloc(sizeof(char) * size);
    if (!env_val)
        return(NULL);
    i = 0;
    while (env[i] && env[i] != '=')
        i++;
    i++;
    j = 0;
    while(env[i])
        env_val[j++] = env[i++];
    env_val[j] = '\0';
    return (env_val);
}

int env_char(int c)
{
    if (ft_isalnum(c) == 1 || c == '_')
        return (1);
    return (0);
}

int len_env_value(char *env)
{
    int i;
    int size;

    size = 0;
    i = 0;
    while (env[i] && env[i] != '=')
        i++;
    i++;
    while (env[i++])
        size++;
    return(size);
}

void	*delete_memmory(void *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (NULL);
}