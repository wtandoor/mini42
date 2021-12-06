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

void init_env(t_mini *mini, char **env)
{
    t_env   *env1;
    t_env   *new;
    int     i;

    env1 = malloc(sizeof(t_env));
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
    return (0);
}

void init_sig(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.exit_status = 0;
}

///////// [main] /////////


void ex_redir_proc(t_mini *mini, t_token *token)
{

}

void mshell(t_mini *mini)
{
    t_token *token;
    int i;

    token = next_ex(mini->start, 0);
    token = (is_type())

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

