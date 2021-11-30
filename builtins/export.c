#include "../includes/minishell.h"
int len_struct(t_env *env)
{
	int i;
	
	i = 0;
	while (env && env->next)
	{
		if (env->value)
		{
			i = i + ft_strlen(env->value);
			i++;
		}

		env = env->next;
	}
	printf("%d", i);
	return (i);
}

char *str_of_env(t_env *sec_env)
{
	int i;
	int j;
	char *temp_env;

	temp_env = (char *)malloc(sizeof (char *) * len_struct(sec_env) + 1);
}

void sort_env(t_env *sec_env)
{
	char *str_env;

	str_env = str_of_env(sec_env);
}

// int export(char **strs, t_env *env, t_env *sec_env)
// {
// 	// int	;

// 	if (strs[1])
// 	{
// 		sort_env(sec_env);
// 		return (SUCCESS);
// 	}
// }