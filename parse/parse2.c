/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 15:45:23 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/18 15:48:45 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_length(char *param, int i, t_env *env, int ret)
{
	char	name_var[4096];
	char	*var_value;
	int		l;

	l = 0;
	if (param[i] == '?')
		return (res_size(ret));
	if (ft_isdigit(param[i]))
		return (0);
	while (param[i] && env_char(param[i]) == 1 && i < 4096)
	{
		name_var[l] = param[i];
		i++;
		l++;
	}
	name_var[l] = '\0';
	var_value = get_env_val(name_var, env);
	l = ft_strlen(var_value);
	delete_memmory(var_value);
	return (l);
}

int	param_malloc(char *s, t_env *env, int err)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (s[++i])
	{
		if (s[i] == -36)
		{
			i++;
			if ((s[i] == '\0' || ft_isalnum(s[i]) == 0) && s[i] != '?')
				size++;
			else
				size += get_length(s, i, env, err);
			if (ft_isdigit(s[i]) == 0)
			{
				while (s[i + 1] && env_char(s[i]))
					i++;
			}
			else
				size--;
		}
		size++;
	}
	return (size);
}

char	*discovering(char *s, t_env *env, int err)
{
	t_disc	str;
	int		new_len;

	new_len = param_malloc(s, env, err);
	str.new1 = (char *)malloc(sizeof(char) * new_len + 1);
	if (!str.new1)
		return (NULL);
	str.i = 0;
	str.j = 0;
	while (str.i < new_len && s[str.j])
	{
		while (s[str.j] == -36)
		{
			str.j++;
			if ((s[str.j] == '\0'
					|| ft_isalnum(s[str.j]) == 0) && s[str.j] != '?')
				str.new1[str.i++] = '$';
			else
				var_in(&str, s, env, err);
		}
		str.new1[str.i++] = s[str.j++];
	}
	str.new1[str.i] = '\0';
	return (str.new1);
}
