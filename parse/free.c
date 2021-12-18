/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 15:26:18 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/18 17:48:18 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token(t_token *start)
{
	while (start && start->next)
	{
		free_memo(start->str);
		start = start->next;
		free_memo(start->prev);
	}
	if (start)
	{
		free_memo(start->str);
		free_memo(start);
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env && env->next)
	{
		tmp = env;
		env = env->next;
		free_memo(tmp->value);
		free_memo(tmp);
	}
	free_memo(env->value);
	free_memo(env);
}

void	*delete_memmory(void *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (NULL);
}

void	delete_token(t_token *start)
{
	while (start && start->next)
	{
		delete_memmory(start->str);
		start = start->next;
		delete_memmory(start->prev);
	}
	if (start)
	{
		delete_memmory(start->str);
		delete_memmory(start);
	}
}

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}
