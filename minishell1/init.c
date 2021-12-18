/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:49:39 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/18 15:01:56 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_sig(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.exit_status = 0;
}

void	reload_std(t_mini *mini)
{
	dup2(mini->in, 0);
	dup2(mini->out, 1);
}

void	init_mini(t_mini *mini)
{
	mini->in = dup(0);
	mini->out = dup(1);
	mini->exit = 0;
	mini->ret = 0;
	mini->no_exec = 0;
}

void	init_fds(t_mini *mini)
{
	mini->fdin = -1;
	mini->fdout = -1;
	mini->pipin = -1;
	mini->pipout = -1;
	mini->pid = -1;
}

int	init_env(t_mini *mini, char **env)
{
	t_env	*env1;
	t_env	*new;
	int		i;

	env1 = (t_env *)malloc(sizeof(t_env));
	if (!env1)
		return (1);
	env1->value = ft_strdup(env[0]);
	env1->next = NULL;
	mini->env = env1;
	i = 1;
	while (env && env[0] && env[i])
	{
		new = (t_env *)malloc(sizeof(t_env));
		if (!new)
			return (1);
		new->value = ft_strdup(env[i++]);
		new->next = NULL;
		env1->next = new;
		env1 = new;
	}
	return (0);
}
