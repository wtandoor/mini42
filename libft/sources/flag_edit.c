/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:54:57 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/15 14:54:58 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	flag_edit(t_flags *flags, va_list parameters)
{
	int	temp;

	if (flags->width < 0)
	{
		temp = va_arg(parameters, int);
		if (temp < 0)
		{
			flags->width = -temp;
			flags->zero = 0;
			flags->minus = 1;
		}
		else
			flags->width = temp;
	}
	if (flags->dot && flags->accuracy < 0)
	{
		temp = va_arg(parameters, int);
		if (temp < 0)
		{
			flags->accuracy = 0;
			flags->dot = 0;
		}
		else
			flags->accuracy = temp;
	}
}
