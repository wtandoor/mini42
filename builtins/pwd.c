#include "../minishell.h"


int pwd(void)
{
	char cwd[5000];

	if (getcwd(cwd, 5000))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	else 
		return (1);
} 
