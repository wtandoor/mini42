/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:33:55 by wtandoor          #+#    #+#             */
/*   Updated: 2021/04/25 16:28:34 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcat(char *dst, const char *src, int size)
{
	int	i;
	int	sizedst;

	if (size <= ft_strlen(dst))
		return (ft_strlen(src) + size);
	sizedst = ft_strlen(dst);
	i = 0;
	while (src[i] != '\0' && sizedst + 1 < size)
		dst[sizedst++] = src[i++];
	dst[sizedst] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}
