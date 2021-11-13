/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:33:29 by wtandoor          #+#    #+#             */
/*   Updated: 2021/04/23 17:33:29 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, int n)
{
	int	i;

	i = 0;
	if (!destination && !source)
		return (0);
	if ((int)destination - (int)source < n)
	{
		i = n - 1;
		while (i >= 0 && i < n)
		{
			((unsigned char *)destination)[i] = ((unsigned char *)source)[i];
			i--;
		}
	}
	else
	{
		while (i < n)
		{
			((unsigned char *)destination)[i] = ((unsigned char *)source)[i];
			i++;
		}
	}
	return (destination);
}
