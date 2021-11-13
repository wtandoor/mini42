/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:33:19 by wtandoor          #+#    #+#             */
/*   Updated: 2021/04/25 17:48:24 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, int n)
{
	int	i;

	i = 0;
	if (!destination && !source)
		return (0);
	while (i < n)
	{
		((unsigned char *)destination)[i] = ((unsigned char *)source)[i];
		if (((unsigned char *)source)[i] == (unsigned char)c)
			return (destination + i + 1);
		i++;
	}
	return (0);
}
