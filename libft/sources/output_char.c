/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:55:09 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/15 14:55:10 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	output_char(t_flags flags, va_list parameters)
{
	char	*c;
	char	temp;
	int		length;

	flag_edit(&flags, parameters);
	temp = va_arg(parameters, int);
	length = 0;
	if (!temp)
		return (c_null(temp, flags));
	c = malloc(2);
	if (!c)
		return (-1);
	c[0] = temp;
	c[1] = '\0';
	length = output_characters(c, flags);
	free(c);
	return (length);
}

int	c_null(char symb, t_flags flags)
{
	int	length;

	length = 0;
	if (flags.minus)
		length = output_char_negative(symb, flags);
	else
		length = output_char_positive(symb, flags);
	return (length);
}

int	output_char_negative(char symb, t_flags flags)
{
	int	length;

	length = 0;
	write(1, &symb, 1);
	length = 1;
	flags.width--;
	while (flags.width > 0)
	{
		length += ft_putchar_fd(' ', 1);
		flags.width--;
	}
	return (length);
}

int	output_char_positive(char symb, t_flags flags)
{
	int	length;
	int	save_length;

	length = 0;
	save_length = 0;
	flags.width--;
	while (flags.width > 0)
	{
		length += ft_putchar_fd(' ', 1);
		flags.width--;
	}
	save_length = length;
	length = 0;
	write(1, &symb, 1);
	length = ++save_length;
	return (length);
}
