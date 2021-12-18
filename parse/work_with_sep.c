/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_sep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 15:33:29 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/18 15:36:37 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_separator(char *str, int i)
{
	if (str[i] && str[i] == '\\' && str[i + 1] && str[i + 1] == ';')
		return (1);
	else if (str[i] && str[i] == '\\' && str[i + 1] && str[i + 1] == '|')
		return (1);
	else if (str[i] && str[i] == '\\' && str[i + 1] && str[i + 1] == '>')
		return (1);
	else if (str[i] && str[i] == '\\' && str[i + 1]
		&& str[i + 1] == '>' && str[i + 2] && str[i + 2] == '>')
		return (1);
	return (0);
}

int	is_separator(char *str, int i)
{
	if (i > 0 && str[i - 1] == '\\' && ft_strchr("<>|;", str[i]))
		return (0);
	else if (ft_strchr("<>|;", str[i]) && quote(str, i) == 0)
		return (0);
	else
		return (0);
}

int	valid_param(t_token *token)
{
	t_token	*prev1;

	if (!token || type_search(token, 1) || type_search(token, 2))
	{
		prev1 = prev(token, 0);
		if (!prev1 || type_search(prev1, 7) || type_search(prev1, 6))
			return (1);
		return (0);
	}
	else
		return (0);
}

int	copy_var(char *new1, char *env_val, int pos)
{
	int	i;

	i = 0;
	while (env_val[i])
		new1[pos++] = env_val[i++];
	return (i);
}

void	var_in(t_disc *str, char *param, t_env *env, int err)
{
	char	*env_val;

	env_val = get_var_value(param, str->j, env, err);
	if (env_val)
		str->i += copy_var(str->new1, env_val, str->i);
	else
		str->i += 0;
	delete_memmory(env_val);
	if (ft_isdigit(param[str->j]) == 0 && param[str->j - 1] != '?')
		while (env_char(param[str->j]) == 1)
			str->j++;
	else
		if (param[str->j - 1] != '?')
			str->j++;
}
