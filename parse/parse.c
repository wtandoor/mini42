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

void init_args(t_token *token, int sep)
{
    if (ft_strcmp(token->str, "") == 0)
        token->type = 0;
    else if (ft_strcmp(token->str, ">") == 0 && sep == 0)
        token->type = 3;
    else if (ft_strcmp(token->str, ">>") == 0 && sep == 0)
        token->type = 4;
    else if (ft_strcmp(token->str, "|") == 0 && sep == 0)
        token->type = 6;
    else if (ft_strcmp(token->str, ";") == 0 && sep == 0)
        token->type = 7;
    else if (ft_strcmp(token->str, "<") == 0 && sep == 0)
        token->type = 5;
    else if (token->prev == NULL || token->prev->type >= 3)
        token->type = 1;
    else
        token->type = 2;
}

int next_a(char *str, int *i)
{
    int count;
    int k;
    char c;

    count = 0;
    k = 0;
    c = ' ';
    while(str[*i + k] && (str[*i + k] !=  ' ' || c != ' '))
    {
        if (c == ' ' && (str[*i + k] == '\'' || str[*i + k] == '\"'))
            c = str[*i + k++];
        else if (c != ' ' && str[*i + k] == c)
        {
            count = count + 2;
            c = ' ';
            k++;
        }
        else
            k++;
        if (str[*i + k - 1] == '\\')
            count--;
    }
    return (k - count + 1);
}

t_token *add_token(char *s, int *i)
{
    t_token *token;
    int j;
    char a;

    j = 0;
    a = ' ';
    token = (t_token *)malloc(sizeof(t_token));
    token->str = malloc(sizeof(char) * next_a(s, i)); //next_alloc
    if (!token || !token->str)
        return (NULL);
    while (s[*i] && (s[*i]!= '\'' || a != ' '))
    {
        if (a == ' ' && (s[*i] == '\'' || s[*i] == '\"'))
            a = s[(*i)++];
        else if (a != ' ' && s[*i] == a)
        {
            a = ' ';
            (*i)++;
        }
        else if (s[*i] == '\\' && (*i)++)
            token->str[j++] = s[(*i)++];
        else
            token->str[j++] = s[(*i)++];
    }
    token->str[j] = '\0';
    return (token);
}

t_token *tokens(char *str)
{
    t_token *next;
    t_token *prev;
    int i;
    int separator;

    i = 0;
    next = NULL;
    prev = NULL;
    skip_chars(str, &i); //skip_space
    while (str[i])
    {
        separator = skip_separator(str, i); //ignore_sep
        next = add_token(str, &i); //next_token
        next->prev = prev;
        if (prev)
            prev->next = prev;
        prev = next;
        init_args(next, separator); //type_arg // comp 
        skip_chars(str, &i);
    }
    if (next)
        next->next = NULL;
    while (next && next->prev)
        next = next->prev;
    return (next);
}

void parse(t_mini *mini)
{
    char *str;
    t_token *token;
    
    signal(SIGINT, &g_sig.sigint);
	signal(SIGQUIT, &g_sig.sigquit);
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
    str = str_new(str);//check
    if (str && str[0] == '$')
        str[0] = (char)(-str[0]);
    mini->start = tokens(str);
    delete_memmory(str);
    take_args(mini);//dopisat'
    token = mini->start;
    while (token)
    {
        if (is_type(token, 2))//check
            type_arg(token, 0);//dopisat' ..init_args 
        token = token->next;
    }
}
