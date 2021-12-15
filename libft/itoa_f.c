/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:57:06 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/15 14:57:07 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_change_sign(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static	int	ft_ilen(int *num, int tail, int flag)
{
	int	len;
	int	n;

	n = *num;
	len = 1;
	if (n < 0 && !flag)
		tail--;
	while (n / 10 != 0)
	{
		n /= 10;
		len++;
	}
	if (tail > 2147483645)
		tail = 2147483645;
	if (tail > len)
		len = tail;
	return (len);
}

char	*itoa_f(int n, int tail, int flag)
{
	int		i;
	int		len;
	char	*string;

	len = ft_ilen(&n, tail, flag);
	if (n < 0)
		len++;
	string = malloc(sizeof(char) * (len + 1));
	if (!string)
		return (NULL);
	i = 0;
	while (i < len)
		string[i++] = '0';
	if (n < 0)
		string[0] = '-';
	string[len] = '\0';
	while (n / 10 != 0)
	{
		string[--len] = ft_change_sign(n % 10) + '0';
		n /= 10;
	}
	string[--len] = ft_change_sign(n % 10) + '0';
	return (string);
}
