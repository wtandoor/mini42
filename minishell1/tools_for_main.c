#include "../minishell.h"


int		line_check(t_mini *mini, t_token *token)
{
	while (token)
	{
		if (is_type(token, "TAI")
		&& (!token->next || is_type(token->next, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", 2);
			token->next ? ft_putstr_fd(token->next->str, 2) : 0;
			token->next ? 0 : ft_putstr_fd("newline", 2);
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