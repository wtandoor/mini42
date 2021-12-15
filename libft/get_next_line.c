/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:56:58 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/15 14:56:59 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_rs(int fd, char *buf, char *l, int rs)
{
	rs = read(fd, buf, BUFFER_SIZE);
	if (rs == -1)
	{
		if (l)
			free(l);
		return (ft_check_rs(buf, rs));
	}
	
	buf[rs] = '\0';
	return (rs);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*l;
	int			rs;

	rs = 1;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf || !line || BUFFER_SIZE <= 0 || fd < 0)
		return (ft_check_rs(buf, -1));
	while (rs)
	{
		if (ft_strchr_gnl(l, '\n') != NULL)
			break ;
		rs = read_rs(fd, buf, l, rs);
		if (rs == -1)
			return (-1);
		l = ft_strjoin(l, buf);
		if (!l)
			return (ft_check_rs(buf, -1));
	}
	*line = ft_substr_gnl(l, 0, strl(l, '\n'), 0);
	l = ft_substr_gnl(l, strl(l, '\n') + 1, (strl(l, '\0') - strl(l, '\n')), 1);
	if (!l && rs)
		return (ft_check_rs(buf, -1));
	return (ft_check_rs(buf, rs));
}
