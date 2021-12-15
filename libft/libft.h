/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:57:10 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/15 14:57:11 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <ctype.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

int		ft_isprint(int ch);
int		ft_isascii(int ch);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_isalnum(int ch);
int		ft_isalpha(int a);
int		ft_isdigit(int arg);
int		ft_atoilen(const char *str, int len);
char	*itoa_f(int n, int tail, int flag);
int		ft_length_u(unsigned long n, int back, int base);
char	*utoa_f(unsigned long n, int back, int flag, int base);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *str1, const char *str2, int n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlcpy(char *dst, const char *src, int size);
int		ft_strlcat(char *dst, const char *src, int size);
char	*ft_strnstr(const char	*big, const char *little, int len);
char	*ft_strchr(const char *str, int ch);
char	*ft_strrchr(const char *str, int ch);
void	*ft_memset(void *destination, int c, int n);
void	ft_bzero(void *s, int n);
void	*ft_memcpy(void *destination, const void *source, int n);
void	*ft_memchr (const void *arr, int c, int n);
int		ft_memcmp(const void *arr1, const void *arr2, int n);
void	*ft_memmove(void *destination, const void *source, int n);
void	*ft_memccpy(void *destination, const void *source, int c, int n);
char	*ft_strdup(const char *s1);
void	*ft_calloc(int num, int size);
int		ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_substr(char const *s, unsigned int start, int len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_putendl_fd(char *s, int fd);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));

#endif