#include "../minishell.h"

void sigint(int c)
{
	(void)c;
	if (g_sig.pid == 0)
	{
		ft_putstr_fd("\b\b  ", STDERR);
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd("\033 minishell ▸ ", STDERR);
		g_sig.exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		g_sig.exit_status = 130;
	}
	g_sig.sigint = 1;
}

void	sigquit(int c)
{
	char *code;

	code = ft_itoa(c);
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("Quit: ", STDERR);
		ft_putendl_fd(code, STDERR);
		g_sig.exit_status = 131;
		g_sig.sigquit = 1;
	}
	else	
		ft_putstr_fd("\b\b  \b\b", STDERR);
	free_memo(code);
}