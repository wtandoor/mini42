#include "get_next_line.h"

char	*ft_substr_gnl(char *s, int start, int len, int flag_free)
{
	int		j;
	char	*new;

	j = 0;
	if (!len && flag_free)
	{
		free(s);
		return (NULL);
	}
	if (!s)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
	{
		free(s);
		return (NULL);
	}
	while (j < len)
		new[j++] = s[start++];
	new[j] = '\0';
	if (flag_free == 1)
		free(s);
	return (new);
}

int	ft_check_rs(char *buf, int rs)
{
	if (buf)
		free(buf);
	if (rs != 0 && rs != -1)
		return (1);
	else
		return (rs);
}

int	strl(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *str, int ch)
{
	if (!str)
		return (NULL);
	while (*str != (char)ch && *str != '\0')
		str++;
	if (*str == (char)ch)
		return (str);
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*new;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = strl(s1, '\0') + strl(s2, '\0');
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (0);
	if (len > 0)
	{
		while (s1 && s1[i] && j < len)
			new[j++] = s1[i++];
		i = 0;
		while (s2 && s2[i] && j < len)
			new[j++] = s2[i++];
	}
	if (s1)
		free(s1);
	new[j] = '\0';
	return (new);
}
