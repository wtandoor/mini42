/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_updatepath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 12:25:20 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/18 16:03:38 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*name_of_env(char *to, char *from)
{
	int	i;

	i = 0;
	while (from[i] && from[i] != '=' && ft_strlen(from) < 4096)
	{
		to[i] = from[i];
		i++;
	}
	to[i] = '\0';
	return (to);
}

int	find_env(char *old_path, t_env *env)
{
	char	old_one[5000];
	char	new_one[5000];

	name_of_env(old_one, old_path);
	while (env && env->next)
	{
		name_of_env(new_one, env->value);
		if (ft_strcmp(old_one, new_one) == 0)
		{
			delete_memmory(env->value);
			env->value = ft_strdup(old_path);
			return (1);
		}
		env = env->next;
	}	
	return (0);
}

int	add_env(char *path, t_env *env)
{
	t_env	*temp;
	t_env	*usable;

	if (env && env->value == NULL)
	{
		env->value = ft_strdup(path);
		return (0);
	}
	usable = (t_env *)malloc(sizeof(t_env));
	if (!usable)
		return (-1);
	usable->value = ft_strdup(path);
	while (env && env->next && env->next->next)
		env = env->next;
	temp = env->next;
	env->next = usable;
	usable->next = temp;
	return (0);
}

int	update_old_path(t_env *env)
{
	char	*cwd;
	char	*old_path;

	cwd = (char *)malloc(sizeof (char *) * 50000);
	getcwd(cwd, 5000);
	if (cwd == NULL)
		return (1);
	old_path = ft_strjoin("OLDPWD=", cwd);
	if (!old_path)
		return (1);
	if (find_env(old_path, env) == 0)
		add_env(old_path, env);
	free_memo(old_path);
	return (0);
}

char	*path_of_env(t_env *env, const char *var, size_t len)
{
	char	*path;
	int		i;
	int		length;
	int		h;

	i = 0;
	h = 0;
	while (env && env->next)
	{
		if (!ft_strncmp(env->value, var, len))
		{
			length = ft_strlen(env->value) - len;
			path = (char *)malloc(sizeof(char) * length + 1);
			if (!path)
				return (NULL);
			while (env->value[i++])
			{
				if (i > (int)len)
					path[h++] = env->value[i];
			}
			path[h] = '\0';
			return (path);
		}
		env = env->next;
	}
	return (NULL);
}
