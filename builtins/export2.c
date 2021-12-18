#include "../minishell.h"

int	export_error(int err, char *strs)
{
	int	i;

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

int	ft_export(char **strs, t_env *env, t_env *sec_env)
{
	int	error;
	int	err_new;

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