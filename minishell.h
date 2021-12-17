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
#define MAX_INT 2147483647
# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7

# define BUFF_SIZE 4096

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
    char *new1;
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

void parse(t_mini *mini);
int		env_char(int c);
char    *ft_quote(char *str, int *i);
int		skip_separator(char *str, int i);
// char	*ft_substr(char *s, unsigned int start, int len);
// char	*ft_strjoin(char *s1, char *s2);
// int     ft_strlen(char *string);
// char	*ft_strdup(char *s1);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *str, int fd);
void    *delete_memmory(void *str);
///signals.c
void	sig_quit(int bits);
void	sig_int(int bits);

///minishell.c
void    ft_close(int fd);
void    update_shell_lvl(t_env *env);
void    init_sig(void);
void    reload_std(t_mini *mini);
int     type_search(t_token *token, int i);

//tools_for_main
int		line_check(t_mini *mini, t_token *token);


//PARSER//
void parser(t_mini *mini);
int quotation(char *stroke, int m_int);
char *spacesof_lines(char *line);
int separation(char *buff, int i);
//parse.c
char *discovering(char *param, t_env *env, int err);
int quote(char *line, int i);



//tools_for_parse

char	*space_line(char *line);
char	*space_alloc(char *line);
char	*get_var_value(const char *arg, int pos, t_env *env, int ret);

//tools_for_parse2.c
int		env_value_len(const char *env);
char	*env_value(char *env);
char		*get_env_name(char *dest, const char *src);

//shlvl.c
int     get_lvl(char *str);
void	skip_space_nl(const char *str, int *i);
int     not_valid_str(char *str);

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

//built/pwd
int pwd(void);

//buil /echo
int ft_echo(char **args);
int num_args(char **args);

///builtins/cd_update_path.c///
int	add_env(char *path, t_env *env);
int ft_cd(char **strs, t_env *env);
///uiltins/export///
int len_struct(t_env *env);
char *str_of_env(t_env *sec_env);
void sort_env(t_env *sec_env);
int ft_export(char **strs, t_env *env, t_env *sec_env);
int	valid_env(char *strs);
int export_error(int err, char *strs);
int ft_export(char **strs, t_env *env, t_env *sec_env);

int    init_env(t_mini *mini, char **env);
void    ft_error(char **strs);
void	close_fd(t_mini *mini);
void    init_fds(t_mini *mini);

///builtins/export2_sort.c//
int len_of_env(char **buff);
void sort_buff(char **buff, int len);
//---------------
int			str_env_len(char **env);
void	sort_env1(char **tab, int env_len);
void	free_buff_n(char **tab);
char		**ft_split(char const *s, char c);
//----------------


//EXECUTE//
//bin
int			box(char *path, char **arg, t_env *env, t_mini *mini);
void ft_close(int fd);
char *check_dir(char *str, char *cmd);
int error_path(char *path);
char *join_path(char *str1, char *str2);
int execute_bin(char **arg, t_env *env, t_mini *mini);
char **create_tab(t_token *token);
int		are_pipe(t_token *token);
void execute_command(t_mini *mini, t_token *token);

int is_type(t_token *token, char *type);
//exit
void	mini_exit(t_mini *mini, char **cmd);
//for_builtin
int is_builtin_command(char *command);
int execute_builtn(char **arg, t_mini *mini);
//free
void	free_token(t_token *start);
void	free_env(t_env *env);
///builtins/unset
void	free_element(t_mini *mini, t_env *env);
int		ft_unset(char **strs, t_mini *mini);
int		ft_env(t_env *env);
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

//TOKENS
//token
t_token	*next(t_token *token, int i);
t_token	*prev(t_token *token, int i);
t_token	*next_ex(t_token *token, int i);

////shlvl///
void    update_shell_lvl(t_env *env);
void init_mini(t_mini *mini);

extern t_sig g_sig;

#endif