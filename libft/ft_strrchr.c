/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:32:33 by wtandoor          #+#    #+#             */
/*   Updated: 2021/04/26 15:07:41 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int		i;
	int		j;
	char	*temp;

	temp = (char *)str;
	i = ft_strlen(temp);
	j = 0;
	while (j < i)
	{
		temp++;
		j++;
	}
	while (*temp != (unsigned char)ch && j > 0)
	{
		j--;
		temp--;
	}
	if (*temp == (unsigned char)ch)
		return (temp);
	return (NULL);
}
