#include "minishell.h"

int check_cmds(char **buff)
{
	int i;

	i = 0;
	if (ft_strcmp(buff[i], "echo") == 0)
		ft_echo(buff);
	if (ft_strcmp(buff[i], "pwd") == 0)
		ft_pwd(buff);
	
}