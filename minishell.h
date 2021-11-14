#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "string.h"
#include "libft/libft.h"
#include "libft/get_next_line.h"

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define SUCCESS 0
#define ERROR 1

typedef struct s_token
{
    char *str;
    int type;
    struct s_token *prev;
    struct s_token *next;
}               t_token;

typedef struct s_env
{
    char    *value;
    struct s_env *next;
}               t_env;

typedef struct	s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}				t_sig;

typedef struct s_mini
{
    t_token *start;
    t_env   *env;
    t_env   *sec_env;
    int in;
    int out;
    int fdin;
    int fdout;
    int pid;
    int pipin;
    int pipout;
    int dad;
    int charge;
    int last;
    int ret;
    int exit;
    int no_exec;
}               t_mini;

void    parser(char *str);
char    *ft_quote(char *str, int *i);
char	*ft_substr(char *s, unsigned int start, int len);
char	*ft_strjoin(char *s1, char *s2);
int     ft_strlen(char *string);
char	*ft_strdup(char *s1);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *str, int fd);
void    *delete_memmory(void *str);

extern t_sig g_sig;

#endif