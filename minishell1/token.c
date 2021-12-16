/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:37:50 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/15 15:38:07 by wtandoor         ###   ########.fr       */
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
			continue ;
		else if (token && token->type == 1 && token->prev->type < 7)
			token = token->next;
	}
	return (token);
}

void	type_arg(t_token *token, int separator)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0 && separator == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && separator == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<") == 0 && separator == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "|") == 0 && separator == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0 && separator == 0)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}
