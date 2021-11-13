/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 15:42:47 by wtandoor          #+#    #+#             */
/*   Updated: 2021/04/25 16:39:26 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[j] != '\0')
	{
		while (s[j] == c)
			j++;
		if (s[j])
			i++;
		while (s[j] != c && s[j])
			j++;
	}
	return (i);
}

static void	ft_free_malloc(int count, char **new)
{
	while (count >= 0)
	{
		free(new[count]);
		count--;
	}
	free(new);
}

static int	ft_split_help(char const *s, char c, char **new, int count_words)
{
	int	start;
	int	end;
	int	count;

	start = 0;
	count = 0;
	while (count < count_words)
	{
		while (s[start] == c)
			start++;
		end = start;
		while (s[end] != c && s[end])
			end++;
		new[count] = ft_substr(s, start, (end - start));
		if (!new[count])
		{
			ft_free_malloc(count, new);
			return (1);
		}
		start = end;
		count++;
	}
	new[count] = 0;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		count_words;
	char	**new;
	int		flag_free;

	flag_free = 0;
	if (!s)
		return (NULL);
	count_words = ft_count_words(s, c);
	new = (char **)malloc((count_words + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	flag_free = ft_split_help(s, c, new, count_words);
	if (flag_free == 1)
		return (NULL);
	return (new);
}
