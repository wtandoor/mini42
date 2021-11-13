/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:34:04 by wtandoor          #+#    #+#             */
/*   Updated: 2021/04/23 17:34:05 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, int n)
{
	int				i;
	unsigned char	*str3;
	unsigned char	*str4;

	str3 = (unsigned char *)str1;
	str4 = (unsigned char *)str2;
	i = 0;
	if (n)
	{
		while (str3[i] != '\0' && str4[i] != '\0' && i < n)
		{
			if (str3[i] != str4[i])
				return (str3[i] - str4[i]);
			if (i < (n - 1))
				i++;
			else
				return (0);
		}
		if (str3[i] != str4[i])
			return (str3[i] - str4[i]);
	}
	return (0);
}
