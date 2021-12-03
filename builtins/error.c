#include "../minishell.h"
void    error(char **strs)
{
	ft_putstr_fd("cd: ", 2);
	if (strs[2])
		ft_putstr_fd("no such file or directory ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(strs[1], 2);
}