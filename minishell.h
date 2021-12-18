/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:30:19 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/18 18:58:31 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}				t_sig;

typedef struct s_disc
{
	char		*new1;
	int			i;
	int			j;
}				t_disc;

typedef struct s_mini
{
	t_token	*start;
	t_env	*env;
	t_env	*sec_env;
	int		in;
	int		out;
	int		fdin;
	int		fdout;
	int		pid;
	int		pipin;
	int		pipout;
	int		dad;
	int		charge;
	int		last;
	int		ret;
	int		exit;
	int		no_exec;
}				t_mini;

////////////////////////final///////////////////////
///[minishell1]///
///init.c///
void	init_sig(void);
void	reload_std(t_mini *mini);
void	init_mini(t_mini *mini);
void	init_fds(t_mini *mini);
int		init_env(t_mini *mini, char **env);
///minishell.c///
void	input(t_mini *mini, t_token *token);
void	redirect(t_mini *mini, t_token *token, int i);
void	ex_redir_proc(t_mini *mini, t_token *token);
void	mshell(t_mini *mini);
///signals.c///
void	sig_int(int bits);
void	sig_quit(int bits);
///token.c///
t_token	*next(t_token *token, int i);
t_token	*prev(t_token *token, int i);
t_token	*next_ex(t_token *token, int i);
void	type_arg(t_token *token, int separator);
///tools_for_main.c///
int		line_check(t_mini *mini, t_token *token);
///types.c///
int		type_search(t_token *token, int i);
int		is_type(t_token *token, char *type);
void	close_fd(t_mini *mini);
int		pipe_ex(t_mini *mini);
///[execute]///
///bin.c///
void	execute_command(t_mini *mini, t_token *token);
void	ft_close(int fd);
char	*check_dir(char *str, char *cmd);
int		error_path(char *path);
int		box(char *path, char **arg, t_env *env, t_mini *mini);
///exit.c///
char	**create_tab(t_token *token);
char	*join_path(char *str1, char *str2);
int		execute_bin(char **arg, t_env *env, t_mini *mini);
void	mini_exit(t_mini *mini, char **cmd);
///for_builtin.c///
int		are_pipe(t_token *token);
int		execute_builtn(char **arg, t_mini *mini);
int		is_a_type(t_token *token, int type);
int		is_builtin_command(char *command);
///[env]///
///env.c///
int		count_str_env(char **env);
int		env_validation(char *env);
char	*get_name(char *dest, char *src);
char	*get_env_val(char *param, t_env *env);
int		init_sec_env(t_mini *mini, char **env_ar);
///shlvl.c///
int		not_valid_str(char *str);
void	skip_space_nl(const char *str, int *i);
int		get_lvl(char *str);
void	update_shell_lvl(t_env *env);
///sort.c///
size_t	get_env_size(t_env *lst);
void	print_new_env(t_env *env);
char	*env_str(t_env *lst);
int		str_env_length(char **env);
void	sort(char **arr, int env_length);
///tools_for_env.c///
char	*env_val1(char *env);
int		env_char(int c);
int		len_env_value(char *env);
void	free_arr2(char **arr);
///[parse]///
///free.c///
void	free_env(t_env *env);
void	delete_token(t_token *start);
void	*delete_memmory(void *str);
void	free_token(t_token *start);
///tools_for_parse.c///
char	*space_alloc(char *line);
char	*space_line(char *line);
char	*get_var_value(const char *arg, int pos, t_env *env, int ret);
int		res_size(int ret);
int		is_char(int c);
///tools_for_parse2.c///
char	*env_value(char *env);
char	*get_env_name(char *dest, const char *src);
int		separation(char *buff, int i);
int		env_value_len(const char *env);
void	skip_chars(char *str, int *i);
///work_with_sep.c///
int		is_separator(char *str, int i);
int		valid_param(t_token *token);
int		copy_var(char *new1, char *env_val, int pos);
void	var_in(t_disc *str, char *param, t_env *env, int err);
int		skip_separator(char *str, int i);
///quote.c///
int		quote(char *line, int i);
void	init_args(t_token *token, int sep);
t_token	*add_token(char *s, int *i);
int		next_a(char *str, int *i);
int		check_quote(t_mini *mini, char **str);
///parse2.c///
char	*discovering(char *s, t_env *env, int err);
int		get_length(char *param, int i, t_env *env, int ret);
int		param_malloc(char *s, t_env *env, int err);
void	parse(t_mini *mini);
void	take_args(t_mini *mini);
t_token	*tokens(char *str);

///[builtns]///

// cd2.c
char	*path_of_env(t_env *env, const char *var, size_t len);
int		go_find_p_env(int variation, t_env *env);
int		ft_cd(char **strs, t_env *env);

//export.c
void	sort_env_write(t_env *env);
void	free_buff_n(char **tab);
char	*str_of_env(t_env *sec_env);
int		len_struct(t_env *env);
int		valid_env(char *strs);

//export2.c
void	sort_env1(char **tab, int env_len);
int		ft_export(char **strs, t_env *env, t_env *sec_env);
int		str_env_len(char **env);
int		export_error(int err, char *strs);
void	free_buff_n(char **tab);
void	error(char **strs);
int		update_old_path(t_env *env);
//free_memmo.c
void	*free_memo(void *s);

//libft.c
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *s);

//echo.c
int		ft_echo(char **args);
int		num_args(char **args);
//pwd.c
int		pwd(void);

//cs_update_path.c
int		find_env(char *old_path, t_env *env);
char	*name_of_env(char *to, char *from);
int		add_env(char *path, t_env *env);
int		update_old_path(t_env *env);
char	*path_of_env(t_env *env, const char *var, size_t len);

//unset.c
int		ft_unset(char **strs, t_mini *mini);
t_env	*ft_lstnew_m(char *content);
t_env	*ft_lstlast_m(t_env *lst);
void	ft_lstadd_back_m(t_env **lst, t_env *new1);

//unset2.c
void	free_element(t_mini *mini, t_env *env);

extern t_sig	g_sig;

#endif