#include "../minishell.h"


int		line_check(t_mini *mini, t_token *token)
{
	while (token)
	{
		if (is_type(token, "TAI")
		&& (!token->next || is_type(token->next, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
			token->next ? ft_putstr_fd(token->next->str, STDERR) : 0;
			token->next ? 0 : ft_putstr_fd("newline", STDERR);
			ft_putendl_fd("'", STDERR);
			mini->ret = 258;
			return (0);
		}
		if (is_type(token, "PE")
		&& (!token->prev || !token->next || is_type(token->prev, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
			ft_putstr_fd(token->str, STDERR);
			ft_putendl_fd("'", STDERR);
			mini->ret = 258;
			return (0);
		}
		token = token->next;
	}
	return (1);
}