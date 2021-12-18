/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:36:15 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/18 15:03:41 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_quit(int bits)
{
	char	*n;

	n = ft_itoa(bits);
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("quit :", 2);
		ft_putendl_fd(n, 2);
		g_sig.exit_status = 131;
		g_sig.sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b\b\b", 2);
	delete_memmory(n);
}

void	sig_int(int bits)
{
	(void)bits;
	if (g_sig.pid == 0)
	{
		ft_putstr_fd("\b\b ", 2);
		ft_putstr_fd("\n", 2);
		g_sig.exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", 2);
		g_sig.exit_status = 130;
	}
	g_sig.sigint = 1;
}
