#include "minishell.h"


int pwd(void)
{
	char cwd[PATH];

	if (getcwd(cwd, PATH))
	{
		ft_putendl_fd(cwd, 1);
		return (1);
	}
	else 
		return (0);
} 
