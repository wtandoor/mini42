/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:38:47 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/18 17:43:30 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*tokens(char *str)
{
	t_token	*next;
	t_token	*prev;
	int		i;
	int		separator;

	i = 0;
	next = NULL;
	prev = NULL;
	skip_chars(str, &i);
	while (str[i])
	{
		separator = skip_separator(str, i);
		next = add_token(str, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		init_args(next, separator);
		skip_chars(str, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}

static void	take_args_add(t_mini *mini, t_token *prev1, t_token *token)
{
	if (prev1)
		token->next = prev1->next;
	else
		token->next = mini->start;
	if (!prev1)
		prev1 = token;
	prev1->next->prev = token;
	if (!mini->start->prev)
		prev1->next = token;
	if (mini->start->prev)
				mini->start = mini->start->prev;
}

void	take_args(t_mini *mini)
{
	t_token	*prev1;
	t_token	*token;

	token = mini->start;
	while (token)
	{
		prev1 = prev(token, 0);
		if (type_search(token, 2) && is_type(prev1, "TAI"))
		{
			while (valid_param(prev1) == 0)
				prev1 = prev1->prev;
			token->prev->next = token->next;
			if (token->next)
				token->next->prev = token->prev;
			token->prev = prev1;
			take_args_add(mini, prev1, token);
		}
		token = token->next;
	}
}

static void	parse_add(char *str, t_mini *mini, t_token *token)
{
	if (str && str[0] == '$')
		str[0] = (char)(-str[0]);
	mini->start = tokens(str);
	delete_memmory(str);
	take_args(mini);
	token = mini->start;
	while (token)
	{
		if (type_search(token, 2))
			init_args(token, 0);
		token = token->next;
	}
}

void	parse(t_mini *mini)
{
	char	*str;
	t_token	*token;

	token = NULL;
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	if (mini->ret)
		ft_putstr_fd("ERROR\n", 2);
	ft_putstr_fd("minishell ▸ ", 2);
	if (get_next_line(0, &str) == -1)
	{
		mini->exit = 1;
		ft_putendl_fd("exit", 2);
	}
	if (g_sig.sigint == 1)
		mini->ret = g_sig.exit_status;
	if (check_quote(mini, &str))
		return ;
	str = space_line(str);
	parse_add(str, mini, token);
}
