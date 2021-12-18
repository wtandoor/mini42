/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:37:49 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/18 17:48:57 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	if (env)
		ft_putendl_fd(env->value, 1);
	return (1);
}

int	is_builtin_command(char *command)
{
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	return (0);
}

int	execute_builtn(char **arg, t_mini *mini)
{
	int	res;

	res = 0;
	if (ft_strcmp(arg[0], "cd") == 0)
		res = ft_cd(arg, mini->env);
	if (ft_strcmp(arg[0], "pwd") == 0)
		res = pwd();
	if (ft_strcmp(arg[0], "echo") == 0)
		res = ft_echo(arg);
	if (ft_strcmp(arg[0], "env") == 0)
		ft_env(mini->env);
	if (ft_strcmp(arg[0], "export") == 0)
		ft_export(arg, mini->env, mini->sec_env);
	if (ft_strcmp(arg[0], "unset") == 0)
		ft_unset(arg, mini);
	return (res);
}

int	is_a_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

int	are_pipe(t_token *token)
{
	while (token && is_a_type(token, 7) == 0)
	{
		if (is_a_type(token, 6))
			return (1);
		token = token->next;
	}
	return (0);
}
