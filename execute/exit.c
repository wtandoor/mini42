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
	ft_putstr_fd("exit ", STDERR);
	cmd[1] ? ft_putendl_fd("❤️", STDERR) : ft_putendl_fd("💚", STDERR);
	if (cmd[1] && cmd[2])
	{
		mini->ret = 1;
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
	}
	else if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		mini->ret = 255;
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
	}
	else if (cmd[1])
		mini->ret = ft_atoi(cmd[1]);
	else
		mini->ret = 0;
}