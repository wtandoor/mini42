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
	// printf("i: %d", i);
	return (i);
}

char *str_of_env(t_env *sec_env) //превращаем список в массив с "\n"
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
	
// while (env->next)
// 		printf("sec_env: %s\n", env->value), env = env->next;
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
		ft_putstr_fd("export: not in the context ", STDERR);
	if (err == 0 || err == -3)
		ft_putstr_fd("export: not an identifire ", STDERR);
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

	// write (1, strs[0], strlen(strs[0]));
	err_new = 0;
	if (!strs[1])
	{
		// while (sec_env->next)
		// printf("sec_env: %s\n", sec_env->value), sec_env = sec_env->next;
		sort_env_write(sec_env);
		// write (1, "1", 1);
		return (SUCCESS);
	}
	else
	{
		// write (1, "2", 1);
		error = valid_env(strs[1]);
		// write (1, "2", 1);
		if (strs[1][0] == '=')
			error = -3;
		// write (1, "3", 1);
		if (error <= 0)
			return (export_error(error, strs[1]));
		// write (1, "4", 1);
		// if (error == 2)
		// 	err_new = 1;
		// else
		// 	err_new = find_env(strs[1], env);
		// printf("%s", env->value);
		err_new = error == 2 ? 1 : find_env(strs[1], env);
		// write (1, "5", 1);
		if (err_new == 0)
		{
			if (error == 1)
				add_env(strs[1], env);
			add_env(strs[1], sec_env);
		}

	}
	//  while (sec_env->next)
	// {
	// 	printf("1) %s\n", sec_env->value);
	// 	sec_env = sec_env->next;
	// }
	return (0);
}