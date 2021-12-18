/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_in_string1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:55:00 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/18 17:29:24 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	zero(char symb, t_flags *flags)
{
	if (symb == '0')
		flags->zero = 1;
	return (1);
}

int	minus(char symb, t_flags *flags)
{
	if (symb == '-')
		flags->minus = 1;
	return (1);
}

int	void_2(char symb, t_flags *flags)
{
	if (symb == ' ')
		flags->space = 1;
	return (1);
}

int	dot(char symb, t_flags *flags)
{
	if (symb == '.')
		flags->dot = 1;
	return (1);
}

int	accuracy(char *s1, t_flags *flags)
{
	int	i;

	i = 0;
	if (s1[i] == '*')
	{
		flags->accuracy = -1;
		i = 1;
	}
	else if (ft_isdigit(s1[i]))
	{
		while (ft_isdigit(s1[i]))
			i++;
		flags->accuracy = ft_atoilen(s1, i);
	}
	return (i);
}
