/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:32:43 by wtandoor          #+#    #+#             */
/*   Updated: 2021/04/23 17:32:55 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(long int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = nb * (-1);
		i++;
	}
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static void	ft_itoa_help(long int nb, int len, char *new)
{
	int			k;
	long int	j;
	int			i;

	i = 1;
	k = 0;
	j = 1;
	if (nb < 0)
	{
		new[k++] = '-';
		nb *= (-1);
	}
	while (i++ != ft_count(nb))
		j *= 10;
	while (k < len)
	{
		new[k++] = nb / j + '0';
		nb %= j;
		j /= 10;
	}
	new[k] = '\0';
}

char	*ft_itoa(int n)
{
	char		*new;
	int			len;
	long int	nb;

	nb = n;
	len = ft_count(nb);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	ft_itoa_help(nb, len, new);
	return (new);
}
