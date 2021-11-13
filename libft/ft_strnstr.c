/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:34:07 by wtandoor          #+#    #+#             */
/*   Updated: 2021/04/26 15:17:45 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char *little, int len)
{
	int		i;
	int		j;
	char	*temp;

	temp = (char *)big;
	i = 0;
	if (*little == '\0')
		return (temp);
	if (len == 0)
		return (NULL);
	while (temp[i] && i < len)
	{
		j = 0;
		while (temp[i + j] == little[j] && little[j] && i + j < len)
			j++;
		if (little[j] == '\0')
			return (&(temp[i]));
		i++;
	}
	return (NULL);
}
