/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_stringfl.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:55:38 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/15 14:55:39 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	search_flags(t_flags *flags, char *s1)
{
	int	i;

	i = 0;
	while (type_flags(s1[i], *flags))
	{
		if (s1[i] == '0' && flags->width == 0
			&& flags->minus == 0 && flags->accuracy == 0)
			i += zero(s1[i], flags);
		else if (s1[i] == '-')
			i += minus(s1[i], flags);
		else if (s1[i] == ' ')
			i += Void(s1[i], flags);
		else if (s1[i] == '.')
			i += dot(s1[i], flags);
		else if ((s1[i] == '*' && flags->dot == 1)
			|| (ft_isdigit(s1[i]) && flags->dot == 1))
			i += accuracy(s1 + i, flags);
		else if (s1[i] == '*' || ft_isdigit(s1[i]))
			i += width(s1 + i, flags);
		else
			flags->type = s1[i++];
	}
	return (i);
}

int	string_flags(t_flags flags, va_list parameters)
{
	int	length;

	length = 0;
	if (flags.type == 'd' || flags.type == 'i')
		length += output_decimal(flags, parameters);
	if (flags.type == 'u')
		length += output_unsigned(flags, parameters);
	if (flags.type == 's')
		length += output_string(flags, parameters);
	if (flags.type == 'c')
		length += output_char(flags, parameters);
	if (flags.type == 'x' || flags.type == 'X')
		length += output_sixteen(flags, parameters);
	if (flags.type == 'p')
		length += output_p(flags, parameters);
	if (flags.type == '%')
		length += output_percentage(flags, parameters);
	if (length < 0)
		return (-1);
	return (length);
}
