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

static int	len_env_value_static(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void	*free_unset(t_mini *mini, t_env *env)
{
	if (env->next)
			mini->env = env->next;
	free_element(mini, env);
	return (0);
}

int	ft_unset(char **strs, t_mini *mini)
{
	t_env	*env;
	t_env	*temp;

	env = mini->env;
	if (!(strs[1]))
		return (0);
	if (ft_strncmp(strs[1], env->value, len_env_value_static(env->value)) == 0)
	{
		free_unset(mini, env);
		return (0);
	}
	while (env && env->next)
	{
		if (ft_strncmp(strs[1], env->next->value, \
			len_env_value_static(env->next->value)) == 0)
		{
			temp = env->next->next;
			free_element(mini, env->next);
			env->next = temp;
			return (0);
		}
		env = env->next;
	}
	return (0);
}

t_env	*ft_lstnew_m(char *content)
{
	t_env	*lst;

	lst = (t_env *)malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	lst->value = content;
	lst->next = NULL;
	return (lst);
}

t_env	*ft_lstlast_m(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}
