#include "../minishell.h"

int	valid_env(char *strs)
{
	int i;

	i = 0;
	if (ft_isdigit(strs[i]) == 1)
		return (0);
	while (strs[i] && strs[i] != '=')
	{
		if (ft_isalnum(strs[i]) == 0)
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
	i = 0;
	while (sec_env && sec_env->next != NULL)
	{
		if (sec_env->value != NULL)
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
	return (temp_env);
}

void sort_env_write(t_env *env)
{
	int		i;
	char	**tab;
	char	*str_env;

	str_env = str_of_env(env);
	tab = ft_split(str_env, '\n');
	free_memo(str_env);
	sort_env1(tab, str_env_len(tab));
	i = 0;
	while (tab[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(tab[i], 1);
		i++;
	}
	free_buff_n(tab);
}

void	free_buff_n(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
			free_memo(tab[i]);
		i++;
	}
	if (tab)
		free_memo(tab);
}


int export_error(int err, char *strs)
{
	int i;

	i = 0;
	if (err == -1)
		ft_putstr_fd("export: not in the context ", 2);
	if (err == 0 || err == -3)
		ft_putstr_fd("export: not an identifire ", 2);
	while (strs[i] && (strs[i] != '=' || err == -3))
	{
		write (2, &strs[i], 1);
		i++;
	}
	write(2, "\n", 1);
	return (2);
}

int ft_export(char **strs, t_env *env, t_env *sec_env)
{
	int	error;
	int err_new;

	err_new = 0;
	if (!strs[1])
	{
		sort_env_write(sec_env);
		return (0);
	}
	else
	{
		error = valid_env(strs[1]);
		if (strs[1][0] == '=')
			error = -3;
		if (error <= 0)
			return (export_error(error, strs[1]));
		err_new = error == 2 ? 1 : find_env(strs[1], env);
		if (err_new == 0)
		{
			if (error == 1)
				add_env(strs[1], env);
			add_env(strs[1], sec_env);
		}
	}
	return (0);
}