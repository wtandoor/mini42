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

int	valid_env(char *strs)
{
	int	i;

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

int	len_struct(t_env *env)
{
	int	i;

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

static int	str_of_env2(t_env *sec_env, char *temp_env)
{
	int	i;
	int	j;

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
	return (i);
}

char	*str_of_env(t_env *sec_env)
{
	int		i;
	char	*temp_env;

	temp_env = (char *)malloc(sizeof (char *) * len_struct(sec_env) + 1);
	if (!temp_env)
		return (NULL);
	i = 0;
	i = str_of_env2(sec_env, temp_env);
	temp_env[i] = '\0';
	return (temp_env);
}

void	sort_env_write(t_env *env)
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
