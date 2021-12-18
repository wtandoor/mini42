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

int	go_find_p_env(int variation, t_env *env)
{
	char	*path;
	int		i;

	path = NULL;
	if (variation == 0)
	{
		update_old_path(env);
		path = path_of_env(env, "HOME", 4);
		if (!path)
			ft_putendl_fd("HOME is missing", 2);
		if (!path)
			return (1);
	}
	else if (variation == 1)
	{
		path = path_of_env(env, "OLDPWD", 6);
		if (!path)
			ft_putendl_fd("OLDPWD is missing", 2);
		if (!path)
			return (1);
		update_old_path(env);
	}
	i = chdir(path);
	free_memo(path);
	return (i);
}

int	ft_cd(char **strs, t_env *env)
{
	int	cd_val;

	if (!strs[1])
		return (go_find_p_env(0, env));
	if (ft_strcmp(strs[1], "-") == 0)
		cd_val = go_find_p_env(1, env);
	else
	{
		update_old_path(env);
		cd_val = chdir(strs[1]);
		if (cd_val < 0)
			cd_val = cd_val * (-1);
		if (cd_val != 0)
			error(strs);
	}
	return (cd_val);
}
