/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:33:46 by wtandoor          #+#    #+#             */
/*   Updated: 2021/04/23 17:33:47 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	char	*temp;

	temp = (char *)str;
	while (*temp != (char)ch && *temp != '\0')
		temp++;
	if (*temp == (char)ch)
		return (temp);
	return (NULL);
}
