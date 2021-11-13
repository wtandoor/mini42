#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>

#define BUFFER_SIZE  1

int		strl(char *str, char c);
char	*ft_strchr(char *str, int ch);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len, int flag_free);
int		get_next_line(int fd, char **line);
int		ft_check_rs(char *buf, int rs);
#endif