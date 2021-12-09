#include "../minishell.h"

/////// [parse] //////

int check_quote(t_mini *mini, char *str)
{
    if (quote(*str, 2147483647))
    {
        ft_putendl_fd("minishell: syntax error with open quotes", STDERR);
        delete_memmory(*str);
        mini->start = NULL;
        mini->ret = 2;
        return (1);
    }
    return (0);
}

int quote(char *line, int i)
{
    int j;
    int start;

    j = 0;
    start = 0;
    while (line[j] && j != i)
    {
        if (j > 0 && line[j - 1] == '\\')
            ;
        else if (start == 0 && line[j] == '\"')
            start = 1;
        else if (start == 0 && line[j] == '\'')
            start == 2;
        else if (start == 1 && line[j] == '\"')
            start = 0;
        else if (start == 2 && line[j] == '\'')
            start = 0;
        j++;
    }
    return (start);
}

void parse(t_mini *mini)
{
    char *str;
    t_token *token;
    
    // signal(SIGINT, &sig_int);
	// signal(SIGQUIT, &sig_quit);
    if (mini->ret)
        ft_putstr_fd("ERROR", STDERR);
    else
        ft_putstr_fd("Not, ERROR", STDERR);
    if (get_next_line(0, &str) == -1)
    {
        mini->exit = 1;
        ft_putendl_fd("exit", STDERR);
    }
    if (g_sig.sigint == 1)
        mini->ret = g_sig.exit_status;
    if (check_quote(mini, &str))
        return ;
    ///
}

/////// [init structs] //////
void init_mini(t_mini *mini)
{
    mini->in = dup(STDIN);
    mini->out = dup(STDOUT);
    mini->exit = 0;
    mini->ret = 0;
    mini->no_exec = 0;
}

void init_fds(t_mini *mini)
{
    mini->fdin = -1;
    mini->fdout = -1;
    mini->pipin = -1;
    mini->pipout = -1;
    mini->pid = -1;
}

void    init_env(t_mini *mini, char **env)
{
    t_env   *env1;
    t_env   *new;
    int     i;

    env1 = (t_env *)malloc(sizeof(t_env));
    if (!env1)
        return (1);
    env1->value = ft_strdup(env[0]);
    env1->next = NULL;
    mini->env = env;
    i = 1;
    while (env1 && env[0] && env[i])
    {
        new = malloc(sizeof(t_env));
        if (!new)
            return (1);
        new->value = ft_strdup(env[i++]);
        new->next = NULL;
        env1->next = new;
    }
}

void delete_token(t_token *start)
{
    while(start && start->next)
    {
        delete_memmory(start->str);
        start = start->next;
        delete_memmory(start->prev);
    }
    if (start)
    {
        delete_memmory(start->str);
        delete_memmory(start);
    }
}

void init_sig(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.exit_status = 0;
}

void reload_std(t_mini *mini)
{
    dup2(mini->in, 0);
    dup2(mini->out, 1);
}

void	close_fd(t_mini *mini)
{
	ft_close(mini->fdin);
	ft_close(mini->fdout);
	ft_close(mini->pipin);
	ft_close(mini->pipout);
}

///////// [main] /////////

int pipe_ex(t_mini *mini)
{
    pid_t pid;
    int pfd[2];

    pipe(pfd);
    pid = fork();
    if (pid == 0)
    {
        ft_close(pfd[1]);
        dup2(pfd[0], 1);
        mini->pipin = pfd[0];
        mini->pid = -1;
        mini->dad = 0;
        mini->no_exec = 0;
        return (2);
    }
    else
    {
        ft_close(pfd[0]);
        dup2(pfd[1], 1);
        mini->pipout = pfd[1];
        mini->pid = pid;
        mini->last = 0;
        return (1);
        }
}

void input(t_mini *mini, t_token *token)
{
    ft_close(mini->fdin);
    mini->fdin = open(token->str, S_IRWXU , O_RDONLY);
    if (mini->fdin == -1)
    {
        ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->str, 2);
		ft_putendl_fd(": No such file or directory", 2);
		mini->ret = 1;
		mini->no_exec = 1;
		return ;
    }
    dup2(mini->fdout, 1);
}

void redirect(t_mini *mini, t_token *token, int i)
{
    ft_close(mini->fdout);
    if (i == 3)
        mini->fdout = open(token->str, O_TRUNC | O_WRONLY | O_CREAT, S_IRWXU);
    else
        mini->fdout = open(token->str, O_APPEND | O_WRONLY | O_CREAT, S_IRWXU);
    if (mini->fdout == -1)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(token->str, 2);
        ft_putendl_fd(": No such file or directory", 2);
        mini->ret = 1;
        mini->no_exec = 1;
        return ;
    }
    dup2(mini->fdout, 1);
}

void ex_redir_proc(t_mini *mini, t_token *token)
{
    t_token *next1;
    t_token *prev1;
    int i;

    prev1 = prev(token, 0);
    next1 = next(token, 0);
    i = 0;
    if (type_search(prev1, 3))
        redirect(mini, token, 3);
    else if (type_search(prev1, 4))
        redirect(mini, token, 4);
    else if (type_search(prev1, 5))
        input(mini,token);
    else if (type_search(prev1, 6))
        i = pipe_ex(mini);
    if (next1 && type_search(next1, 7) == 0 && i != 1)
        ex_redir_proc(mini, next1->next);
    if ((type_search(prev1, 7) || type_search(prev1, 6) || !prev1) && i != 1 && mini->no_exec == 0)
        execute_command(mini, token);
}

int type_search(t_token *token, int i)
{
    if (token && token->type == i)
        return (1);
    else
        return (0);
}

int is_type(t_token *token, char *type)
{
    if (ft_strchr(type, 'I') && type_search(token, 5))
        return (1);
    else if (ft_strchr(type, ' ') && type_search(token, 0))
        return (1);
    else if (ft_strchr(type, 'X') && type_search(token, 1))
        return (1);
    else if (ft_strchr(type, 'x') && type_search(token, 2))
        return (1);
    else if (ft_strchr(type, 'A') && type_search(token, 4))
        return (1);
    else if (ft_strchr(type, 'T') && type_search(token, 3))
        return (1);
    else if (ft_strchr(type, 'P') && type_search(token, 6))
        return (1);
    else if (ft_strchr(type, 'E') && type_search(token, 7))
        return (1);
}

void mshell(t_mini *mini)
{
    t_token *token;
    int i;

    token = next_ex(mini->start, 0);
    token = (is_type(mini->start, "TAI")) ? mini->start->next : token;
    while (mini->exit == 0 && token)
    {
        mini->charge = 1;
        mini->dad = 1;
        mini->last = 1;
        ex_redir_proc(mini, token);
        reload_std(mini);
        close_fd(mini);
        init_fds(mini);
        waitpid(-1, &i, 0);
        i = WEXITSTATUS(i);
        mini->ret = (mini->last == 0) ? i : mini->ret;
        if (mini->dad == 0)
        {
            delete_token(mini->start);
            exit(mini->ret);
        }
        mini->no_exec = 0;
        token = next_ex(token, 1);
    }
}


int main(int argc, char **argv, char **env)
{
    t_mini mini;

    (void)argc;
    (void)argv;
    init_mini(&mini);
    init_fds(&mini);
    init_env(&mini, env);
    init_sec_env(&mini, env);
    update_shell_level(mini.env);
    while (mini.exit == 0)
    {
        init_sig();
        parser(&mini);
        if (mini.start != NULL && line_check(&mini, mini.start))
            mshell(&mini);
        free_token(mini.start);
    }
    free_env(mini.env);
    free_env(mini.sec_env);
    return(mini.ret);
}

