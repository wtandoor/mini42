/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:34:15 by wtandoor          #+#    #+#             */
/*   Updated: 2021/04/23 17:34:15 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_char(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		len;
	char	*new;

	if (set == 0 || s1 == 0)
		return ((char *)s1);
	start = 0;
	len = ft_strlen(s1);
	end = len;
	while (ft_find_char(set, s1[start]) != 0 && s1[start])
		start++;
	while (ft_find_char(set, s1[end - 1]) != 0 && end > start)
		end--;
	new = malloc(sizeof(char) * (end - start + 1));
	if (!new)
		return (NULL);
	len = 0;
	while (start < end)
		new[len++] = s1[start++];
	new[len] = '\0';
	return (new);
}
