/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 20:23:37 by wtandoor          #+#    #+#             */
/*   Updated: 2021/04/22 20:23:38 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(int num, int size)
{
	void	*new;
	int		i;

	i = num * size;
	new = malloc(i);
	if (!new)
		return (0);
	ft_bzero(new, i);
	return (new);
}
