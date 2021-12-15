/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:55:19 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/15 14:55:20 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*string_edit_p(unsigned long nb, t_flags flags)
{
	char	*s1;

	if (flags.zero && !flags.accuracy && !flags.dot && flags.width)
		s1 = utoa_f(nb, flags.width, 0, 16);
	else
		s1 = utoa_f(nb, flags.accuracy, 1, 16);
	if (!s1)
		return (0);
	return (s1);
}

int	output_p(t_flags flags, va_list parameters)
{
	int				length;
	char			*s1;
	char			*temp;
	unsigned long	t;

	flag_edit(&flags, parameters);
	length = 0;
	t = (unsigned long)va_arg(parameters, void *);
	if (!t && !flags.accuracy && flags.dot)
		s1 = ft_strdup("");
	else
		s1 = string_edit_p(t, flags);
	if (!s1)
		return (-1);
	temp = s1;
	s1 = ft_strjoin("0x", s1);
	free(temp);
	if (!s1)
		return (-1);
	length = output_characters(s1, flags);
	free(s1);
	return (length);
}
