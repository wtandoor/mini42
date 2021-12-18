/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:37:50 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/18 15:04:32 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*next(t_token *token, int i)
{
	if (token && i)
		token = token->next;
	while (token && token->type < 3)
		token = token->next;
	return (token);
}

t_token	*prev(t_token *token, int i)
{
	if (token && i)
		token = token->prev;
	while (token && token->type < 3)
		token = token->prev;
	return (token);
}

t_token	*next_ex(t_token *token, int i)
{
	if (token && i)
		token = token->next;
	while (token && token->type != 1)
	{
		token = token->next;
		if (token && token->type == 1 && token->prev == NULL)
			;
		else if (token && token->type == 1 && token->prev->type < 7)
			token = token->next;
	}
	return (token);
}

void	type_arg(t_token *token, int separator)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = 0;
	else if (ft_strcmp(token->str, ">") == 0 && separator == 0)
		token->type = 3;
	else if (ft_strcmp(token->str, ">>") == 0 && separator == 0)
		token->type = 4;
	else if (ft_strcmp(token->str, "<") == 0 && separator == 0)
		token->type = 5;
	else if (ft_strcmp(token->str, "|") == 0 && separator == 0)
		token->type = 6;
	else if (ft_strcmp(token->str, ";") == 0 && separator == 0)
		token->type = 7;
	else if (token->prev == NULL || token->prev->type >= 3)
		token->type = 1;
	else
		token->type = 2;
}
