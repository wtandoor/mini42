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

// static int	ft_count_words(char const *s, char c)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (s[j] != '\0')
// 	{
// 		while (s[j] == c)
// 			j++;
// 		if (s[j])
// 			i++;
// 		while (s[j] != c && s[j])
// 			j++;
// 	}
// 	return (i);
// }

// static void	ft_free_malloc(int count, char **new)
// {
// 	while (count >= 0)
// 	{
// 		free(new[count]);
// 		count--;
// 	}
// 	free(new);
// }

// static int	ft_split_help(char const *s, char c, char **new, int count_words)
// {
// 	int	start;
// 	int	end;
// 	int	count;

// 	start = 0;
// 	count = 0;
// 	while (count < count_words)
// 	{
// 		while (s[start] == c)
// 			start++;
// 		end = start;
// 		while (s[end] != c && s[end])
// 			end++;
// 		new[count] = ft_substr(s, start, (end - start));
// 		// printf("%s\n", new[count]);
// 		if (!new[count])
// 		{
// 			ft_free_malloc(count, new);
// 			return (1);
// 		}
// 		start = end;
// 		count++;
// 	}
// 	new[count] = 0;
// 	int i = 0;
// 	while (new[i])	
// 		printf("split%s", new[i]), i++;
// 	return (0);
// }

// char	**ft_split(char const *s, char c)
// {
// 	int		count_words;
// 	char	**new;
// 	int		flag_free;

// 	// printf("%s", s);
// 	flag_free = 0;
// 	if (!s)
// 		return (NULL);
// 	count_words = ft_count_words(s, c);
// 	new = (char **)malloc((count_words + 1) * sizeof(char *));
// 	if (!new)
// 		return (NULL);
// 	flag_free = ft_split_help(s, c, new, count_words);
// 	if (flag_free == 1)
// 		return (NULL);
// 	int i = 0;
// 	// while (new[i])
// 		// printf("split: %s\n", new[i]), i++;
// 	return (new);
// }



#include "libft.h"

static int	word_count(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		count++;
		while (s[i] != c && s[i] != '\0')
			i++;
		while (s[i] == c)
			i++;
	}
	// printf("\n%d\n", count);
	return (count);
}

static int	letter_count(char const *s, char c, int index)
{
	int		count;

	count = 0;
	while (s[index] != c && s[index] != '\0')
	{
		count++;
		index++;
	}
	// printf("lettet_count \n%d\n", count);
	return (count);
}

char		**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	// printf("%s", s); // c этой ерундой все работает
	if (!s || !c || !(tab = malloc(sizeof(char *) * (word_count(s, c) + 1))))
		return (NULL);
	while (s[k] == c)
	{
		// printf("k = %d %c\n", k, s[k]);
		k++;
	}
	while (s[k] != '\0')
	{
		j = 0;
		if (!(tab[i] = malloc(sizeof(char) * letter_count(s, c, k) + 1)))
			return (NULL);
		while (s[k] != c && s[k] != '\0')
			tab[i][j++] = s[k++];
		tab[i][j] = '\0';
		while (s[k] == c)
			k++;
		i++;
	}
	tab[i] = NULL;
		
	i = 0;
	// while (tab[i])
	// 	printf("split: %s\n", tab[i]), i++;
	return (tab);
}