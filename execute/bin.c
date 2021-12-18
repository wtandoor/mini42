/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:38:32 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/18 15:15:19 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	box(char *path, char **arg, t_env *env, t_mini *mini)
{
	char	**env_arr;
	char	*p;
	int		res;

	res = 0;
	g_sig.pid = fork();
	if (g_sig.pid == 0)
	{
		p = env_str(env);
		env_arr = ft_split(p, '\n');
		delete_memmory(p);
		if (ft_strchr(path, '/') != NULL)
			execve(path, arg, env_arr);
		res = error_path(path);
		free_arr2(env_arr);
		free_token(mini->start);
		exit(res);
	}
	else
		waitpid(g_sig.pid, &res, 0);
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (g_sig.exit_status);
	if (res == 32256 || res == 32512)
		res = res / 256;
	else
		res = !!res;
	return (res);
}

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

char	*check_dir(char *str, char *cmd)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;

	path = NULL;
	folder = opendir(str);
	if (!folder)
		return (NULL);
	item = readdir(folder);
	while (item)
	{
		if (ft_strcmp(item->d_name, cmd) == 0)
			path = join_path(str, item->d_name);
		item = readdir(folder);
	}
	closedir(folder);
	return (path);
}

int	error_path(char *path)
{
	DIR	*folder;
	int	fd;
	int	res;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", 2);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd("No such file in directory", 2);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd("Is a directory", 2);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd("Permission denied", 2);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		res = 127;
	else
		res = 126;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (res);
}

void	execute_command(t_mini *mini, t_token *token)
{
	char	**command;
	int		i;

	if (mini->charge == 0)
		return ;
	i = 0;
	command = create_tab(token);
	while (command && command[i])
	{
		command[i] = discovering(command[i], mini->env, mini->ret);
		i++;
	}
	if (command && ft_strcmp(command[0], "exit") == 0 && are_pipe(token) == 0)
		mini_exit(mini, command);
	else if (command && is_builtin_command(command[0]))
		mini->ret = execute_builtn(command, mini);
	else if (command)
		mini->ret = execute_bin(command, mini->env, mini);
	free_arr2(command);
	ft_close(mini->pipin);
	ft_close(mini->pipout);
	mini->pipin = -1;
	mini->pipout = -1;
	mini->charge = 0;
}
