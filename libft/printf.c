/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:57:13 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/15 14:57:14 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list	parameters;
	char	*s1;
	int		length;

	s1 = ft_strdup(s);
	length = 0;
	if (!s1)
		return (-1);
	va_start(parameters, s);
	length = output(s1, parameters);
	va_end(parameters);
	free(s1);
	return (length);
}
