#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include "libft/libft.h"
#include "libft/get_next_line.h"
#include <readline/history.h>
#include <readline/readline.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define PATH 5000
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

typedef struct s_disc
{
    char *new;
    int i;
    int j;
}               t_disc;

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
// char	*ft_substr(char *s, unsigned int start, int len);
// char	*ft_strjoin(char *s1, char *s2);
// int     ft_strlen(char *string);
// char	*ft_strdup(char *s1);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *str, int fd);
void    *delete_memmory(void *str);

/////BUILTINS/////
int     update_old_path(t_env *env);
int     find_env(char *old_path, t_env *env);
char    *name_of_env(char *to, char *from);
void	*free_memo(void *s);

////should be deleted later////
void	ft_lstadd_back_m(t_env **lst, t_env *new1);
t_env	*ft_lstlast_m(t_env *lst);
t_env	*ft_lstnew_m(char *content);

char	*ft_strjoin(char const *s1, char const *s2);

//builtins
void    error(char **strs);

///builtins/cd_update_path.c///
int	add_env(char *path, t_env *env);
///uiltins/export///
int len_struct(t_env *env);
char *str_of_env(t_env *sec_env);
void sort_env(t_env *sec_env);
int ft_export(char **strs, t_env *env, t_env *sec_env);
void init_env(t_mini *mini, char **env);
void    ft_error(char **strs);

/////env//////

int str_env_length(char **env);
size_t get_env_size(t_env *lst);
char    *env_str(t_env *lst);
void print_new_env(t_env *env);
void    sort(char **arr, int env_length);
int init_sec_env(t_mini *mini, char **env_ar);
int count_str_env(char **env);
int env_validation(char *env);
char *get_env_val(char *param, t_env *env);
char *get_name(char *dest, char *src);
int len_env_value(char *env);
int env_char(int c);
char *env_val1(char *env);
void free_arr2(char **arr);

////exec////
int			box(char *path, char **arg, t_env *env, t_mini *mini);
void ft_close(int fd);
char *check_dir(char *str, char *cmd);
int error_path(char *path);
char *join_path(char *str1, char *str2);
int execute_bin(char **arg, t_env *env, t_mini *mini);
char **create_tab(t_token *token);
void execute_command(t_mini *mini, t_token *token);

////parse////
int check_quote(t_mini *mini, char *str);
int quote(char *line, int i);
void init_args(t_token *token, int sep);
int next_a(char *str, int *i);
t_token *add_token(char *s, int *i);
void skip_chars(char *str, int *i);
t_token *tokens(char *str);
int skip_separator(char *str, int i);
int is_separator(char *str, int i);
int valid_param(t_token *token);
void parse(t_mini *mini);
void take_args(t_mini *mini);
int copy_var(char *new, char *env_val, int pos);
void var_in(t_disc *str, char *param, t_env *env, int err);
int get_length(char *param, int i, t_env *env, int ret);
int res_size(int ret);
int param_malloc(char *param, t_env *env, int err);
int		is_char(int c);
char *discovering(char *param, t_env *env, int err);

extern t_sig g_sig;

#endif