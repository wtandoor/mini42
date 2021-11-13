/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:33:32 by wtandoor          #+#    #+#             */
/*   Updated: 2021/04/23 17:33:32 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, int n)
{
	unsigned char	*temp;

	temp = (unsigned char *)destination;
	while (n-- > 0)
	{
		*temp = (char)c;
		temp++;
	}
	return (destination);
}
