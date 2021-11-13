/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 20:23:25 by wtandoor          #+#    #+#             */
/*   Updated: 2021/04/25 16:39:21 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoilen(const char *str, int len)
{
	int		i;
	int		flag_sign;
	int		rez;

	i = 0;
	flag_sign = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			flag_sign = -1;
		i++;
	}
	rez = 0;
	while (str[i] >= 48 && str[i] <= 57 && i <= len)
		rez = rez * 10 + str[i++] - '0';
	if (flag_sign == -1)
		return (-rez);
	return (rez);
}
