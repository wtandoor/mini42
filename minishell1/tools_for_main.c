/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:20:28 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/18 17:35:18 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	line_check_add(t_token *token, t_mini *mini)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putstr_fd(token->str, 2);
	ft_putendl_fd("'", 2);
	mini->ret = 258;
}

int	line_check(t_mini *mini, t_token *token)
{
	while (token)
	{
		if (is_type(token, "TAI")
			&& (!token->next || is_type(token->next, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", 2);
			if (token->next)
				ft_putstr_fd(token->next->str, 2);
			if (!token->next)
				ft_putstr_fd("newline", 2);
			ft_putendl_fd("'", 2);
			mini->ret = 258;
			return (0);
		}
		if (is_type(token, "PE")
			&& (!token->prev || !token->next || is_type(token->prev, "TAIPE")))
		{
			line_check_add(token, mini);
			return (0);
		}
		token = token->next;
	}
	return (1);
}
