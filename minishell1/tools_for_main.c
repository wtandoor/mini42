/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:20:28 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/18 14:24:02 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			ft_putstr_fd("bash: syntax error near unexpected token `", 2);
			ft_putstr_fd(token->str, 2);
			ft_putendl_fd("'", 2);
			mini->ret = 258;
			return (0);
		}
		token = token->next;
	}
	return (1);
}
