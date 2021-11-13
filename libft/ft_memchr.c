/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:33:22 by wtandoor          #+#    #+#             */
/*   Updated: 2021/04/23 17:33:22 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)arr)[i] == (unsigned char)c)
			return ((void *)(arr + i));
		i++;
	}
	return (NULL);
}
