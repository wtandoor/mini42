/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:07:53 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/18 15:16:57 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_strisnum(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	mini_exit(t_mini *mini, char **cmd)
{
	mini->exit = 1;
	if (cmd[1] && cmd[2])
	{
		mini->ret = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	else if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		mini->ret = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (cmd[1])
		mini->ret = ft_atoi(cmd[1]);
	else
		mini->ret = 0;
}

char	*join_path(char *str1, char *str2)
{
	char	*temp;
	char	*new;

	temp = ft_strjoin(str1, "/");
	new = ft_strjoin(temp, str2);
	delete_memmory(temp);
	return (new);
}

int	execute_bin(char **arg, t_env *env, t_mini *mini)
{
	int		i;
	char	**bin;
	char	*path;
	int		res;

	i = 0;
	res = 127;
	while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
		env = env->next;
	if (env == NULL || env->next == NULL)
		return (box(arg[0], arg, env, mini));
	bin = ft_split(env->value, ':');
	if (!arg[0] && !bin[0])
		return (1);
	i = 1;
	path = check_dir(bin[0] + 5, arg[0]);
	while (arg[0] && bin[i] && path == NULL)
		path = check_dir(bin[i++], arg[0]);
	if (path != NULL)
		res = box(path, arg, env, mini);
	else
		res = box(arg[0], arg, env, mini);
	free_arr2(bin);
	delete_memmory(path);
	return (res);
}

char	**create_tab(t_token *token)
{
	t_token	*token1;
	char	**tab;
	int		i;

	if (!token)
		return (NULL);
	token1 = token->next;
	i = 2;
	while (token1 && token1->type < 3)
	{
		token1 = token1->next;
		i++;
	}
	tab = (char **)malloc(sizeof(char *) * i);
	token1 = token->next;
	tab[0] = token->str;
	i = 1;
	while (token1 && token1->type < 3)
	{
		tab[i++] = token1->str;
		token1 = token1->next;
	}
	tab[i] = NULL;
	return (tab);
}
