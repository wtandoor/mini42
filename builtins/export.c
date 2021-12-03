#include "../minishell.h"

// FOR EXPORT gcc builtins/cd_updatepath.c  builtins/free_memo.c -g builtins/libft.c libft/ft_putendl_fd.c 
// libft/ft_strncmp.c libft/ft_putstr_fd.c builtins/error.c builtins/export.c libft/ft_isalnum.c libft/ft_isdigit.c libft/ft_isalpha.c 



int	valid_env(char *strs)
{
	int i;

	i = 0;
	if (ft_isdigit(strs[i]) == 1)
		return (0);
	while (strs[i] && strs[i] != '=')
	{
		if (ft_isalnum(strs[i]))
			return (-1);
		i++;
	}
	if (strs[i] != '=')
		return (2);
	return (1);
}

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
	if (!temp_env)
		return (NULL);
	while (sec_env && sec_env->next)
	{
		if (sec_env->value != 0)
		{
			j = 0;
			while (sec_env->value[j])
			{
				temp_env[i] = sec_env->value[j];
				i++;
				j++;
			}
		}
		if (sec_env->next->next != NULL)
			temp_env[i++] = '\n';
		sec_env = sec_env->next;
	}
	temp_env[i] = '\0';
	return (SUCCESS);
}

void sort_env(t_env *sec_env)
{
	char *str_env;

	str_env = str_of_env(sec_env);
}

int export_error(int err, char *strs)
{
	int i;

	i = 0;
	if (err == -1)
		ft_putstr_fd("export: not in the context", STDERR);
	if (err == 0 || err == -3)
		ft_putstr_fd("export: not an identifire", STDERR);
	while (strs[i] && (strs[i] != '=' || err == -3))
	{
		write (STDERR, &strs[i], 1);
		i++;
	}
	write(STDERR, "\n", 1);
	return (ERROR);
}

int ft_export(char **strs, t_env *env, t_env *sec_env)
{
	int	error;
	int err_new;

	if (strs[1])
	{
		sort_env(sec_env);
		return (SUCCESS);
	}
	else
	{
		error = valid_env(strs[1]);
		if (strs[1][0] == '=')
			error = -3;
		if (error <= 0)
			return (export_error(error, strs[1]));
		if (error == 2)
			err_new = 1;
		else
			err_new = find_env(strs[1], env);
		if (err_new == 0)
		{
			if (error == 1)
				add_env(strs[1], env);
			add_env(strs[1], sec_env);
		}

	}
	return (0);
}