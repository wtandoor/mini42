/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:33:27 by wtandoor          #+#    #+#             */
/*   Updated: 2021/04/23 17:33:27 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, int n)
{
	unsigned char	*src;
	unsigned char	*dst;

	dst = (unsigned char *)destination;
	src = (unsigned char *)source;
	if (destination == source)
		return (destination);
	while (n--)
	{
		*dst = *src;
		dst++;
		src++;
	}
	return (destination);
}
