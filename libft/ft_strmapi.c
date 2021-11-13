/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:34:02 by wtandoor          #+#    #+#             */
/*   Updated: 2021/04/23 17:34:02 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new;
	int		len;
	int		j;

	j = 0;
	if (s == 0)
		return (NULL);
	len = ft_strlen(s);
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	while (j < len)
	{
		new[j] = (*f)(j, s[j]);
		j++;
	}
	new[j] = '\0';
	return (new);
}
