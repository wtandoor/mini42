#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "string.h"
#include <readline/history.h>
#include <readline/readline.h>
#include "../libft/libft.h"
#include "../libft/get_next_line.h"

#define STDIN 0
#define STDOUT 1
#define STDERR 2
# define PATH 5000





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
char	*ft_strdup(const char *s1);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *str, int fd);
void    *delete_memmory(void *str);

/////BUILTINS/////
int     update_old_path(t_env *env);
int     find_env(char *old_path, t_env *env);
char    *name_of_env(char *to, char *from);
void	*free_memo(void *s);

////should be deleted later////
void	ft_lstadd_back_m(t_env **lst, t_env *new);
t_env	*ft_lstlast_m(t_env *lst);
t_env	*ft_lstnew_m(char *content);

char	*ft_strjoin(char const *s1, char const *s2);


// extern t_sig g_sig;

#endif