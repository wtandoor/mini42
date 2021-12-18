/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:33:52 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/18 15:12:40 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_sig	g_sig;

void	input(t_mini *mini, t_token *token)
{
	ft_close(mini->fdin);
	mini->fdin = open(token->str, O_RDONLY, S_IRWXU);
	if (mini->fdin == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->str, 2);
		ft_putendl_fd(": No such file or directory", 2);
		mini->ret = 1;
		mini->no_exec = 1;
		return ;
	}
	dup2(mini->fdin, 0);
}

void	redirect(t_mini *mini, t_token *token, int i)
{
	ft_close(mini->fdout);
	if (i == 3)
		mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (mini->fdout == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->str, 2);
		ft_putendl_fd(": No such file or directory", 2);
		mini->ret = 1;
		mini->no_exec = 1;
		return ;
	}
	dup2(mini->fdout, 1);
}

void	ex_redir_proc(t_mini *mini, t_token *token)
{
	t_token	*next1;
	t_token	*prev1;
	int		i;

	prev1 = prev(token, 0);
	next1 = next(token, 0);
	i = 0;
	if (type_search(prev1, 3))
		redirect(mini, token, 3);
	else if (type_search(prev1, 4))
		redirect(mini, token, 4);
	else if (type_search(prev1, 5))
		input(mini, token);
	else if (type_search(prev1, 6))
		i = pipe_ex(mini);
	if (next1 && type_search(next1, 7) == 0 && i != 1)
		ex_redir_proc(mini, next1->next);
	if ((type_search(prev1, 7) || type_search(prev1, 6)
			|| !prev1) && i != 1 && mini->no_exec == 0)
		execute_command(mini, token);
}

void	mshell(t_mini *mini)
{
	t_token	*token;
	int		i;

	token = next_ex(mini->start, 0);
	if (is_type(mini->start, "TAI"))
		token = mini->start->next;
	while (mini->exit == 0 && token)
	{
		mini->charge = 1;
		mini->dad = 1;
		mini->last = 1;
		ex_redir_proc(mini, token);
		reload_std(mini);
		close_fd(mini);
		init_fds(mini);
		waitpid(-1, &i, 0);
		i = WEXITSTATUS(i);
		if (!mini->last)
			mini->ret = i;
		if (mini->dad == 0)
			exit(mini->ret);
		mini->no_exec = 0;
		token = next_ex(token, 1);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	init_mini(&mini);
	init_fds(&mini);
	init_env(&mini, env);
	init_sec_env(&mini, env);
	update_shell_lvl(mini.env);
	while (mini.exit == 0)
	{
		init_sig();
		parse(&mini);
		if (mini.start != NULL && line_check(&mini, mini.start))
			mshell(&mini);
		free_token(mini.start);
	}
	free_env(mini.env);
	free_env(mini.sec_env);
	return (mini.ret);
}
