/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:50:21 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/18 15:05:42 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	type_search(t_token *token, int i)
{
	if (token && token->type == i)
		return (1);
	else
		return (0);
}

int	is_type(t_token *token, char *type)
{
	if (ft_strchr(type, 'I') && type_search(token, 5))
		return (1);
	else if (ft_strchr(type, ' ') && type_search(token, 0))
		return (1);
	else if (ft_strchr(type, 'X') && type_search(token, 1))
		return (1);
	else if (ft_strchr(type, 'x') && type_search(token, 2))
		return (1);
	else if (ft_strchr(type, 'A') && type_search(token, 4))
		return (1);
	else if (ft_strchr(type, 'T') && type_search(token, 3))
		return (1);
	else if (ft_strchr(type, 'P') && type_search(token, 6))
		return (1);
	else if (ft_strchr(type, 'E') && type_search(token, 7))
		return (1);
	return (0);
}

void	close_fd(t_mini *mini)
{
	ft_close(mini->fdin);
	ft_close(mini->fdout);
	ft_close(mini->pipin);
	ft_close(mini->pipout);
}

int	pipe_ex(t_mini *mini)
{
	pid_t	pid;
	int		pfd[2];

	pipe(pfd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(pfd[1]);
		dup2(pfd[0], 1);
		mini->pipin = pfd[0];
		mini->pid = -1;
		mini->dad = 0;
		mini->no_exec = 0;
		return (2);
	}
	else
	{
		ft_close(pfd[0]);
		dup2(pfd[1], 1);
		mini->pipout = pfd[1];
		mini->pid = pid;
		mini->last = 0;
		return (1);
	}
}
