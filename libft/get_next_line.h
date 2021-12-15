/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:57:01 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/15 14:57:02 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include "libft.h"

#define BUFFER_SIZE  1

int		strl(char *str, char c);
char	*ft_strchr_gnl(char *str, int ch);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_substr_gnl(char *s, int start, int len, int flag_free);
int		get_next_line(int fd, char **line);
int		ft_check_rs(char *buf, int rs);
#endif