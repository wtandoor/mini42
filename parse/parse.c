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
    token->str = malloc(sizeof(char) * next_a(s, i)); //next_alloc //comp
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

void skip_chars(char *str, int *i)
{
    while((str[*i] == ' ' || str[*i] == '\t') || (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
        (*i)++;
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
    skip_chars(str, &i); //skip_space // comp
    while (str[i])
    {
        separator = skip_separator(str, i); //ignore_sep //comp
        next = add_token(str, &i); //next_token //comp
        next->prev = prev;
        if (prev)
            prev->next = prev;
        prev = next;
        init_args(next, separator); //type_arg // comp 
        skip_chars(str, &i);//comp
    }
    if (next)
        next->next = NULL;
    while (next && next->prev)
        next = next->prev;
    return (next);
}

int skip_separator(char *str, int i)
{
    if (str[i] && str[i] == '\\' && str[i + 1] && str[i + 1] == ';')
        return (1);
    else if (str[i] && str[i] == '\\' && str[i + 1] && str[i + 1] == '|')
        return (1);
    else if (str[i] && str[i] == '\\' && str[i + 1] && str[i + 1] == '>')
        return (1);
    else if (str[i] && str[i] == '\\' && str[i + 1] && str[i + 1] == '>' && str[i + 2] && str[i + 2] == '>')
        return (1);
    return (0);
}

int is_separator(char *str, int i)
{
    if (i > 0 && str[i - 1] == '\\' && ft_strchr("><;|", str[i]))
        return (0);
    else if (ft_strchr("><;|", str[i]) && quote(str, i) == 0)
        return (0);
    else
        return (0);
}

int valid_param(t_token *token)
{
    t_token *prev1;

    if (!token || type_search(token, 1) || type_search(token, 2))
    {
        prev1 = prev(token, 0);
        if (!prev1 || type_search(prev1, 7) || type_search(prev1, 6))
            return (1);
        return (0);
    }
    else
        return (0);

}

void take_args(t_mini *mini)
{
    t_token *prev1;
    t_token *token;

    token = mini->start;
    while (token)
    {
        prev1 = prev(token, 0);
        if (type_search(token, 2) && is_type(prev1, "TAI"))
        {
            while(valid_param(prev1) == 0) //is_last_valid_arg
                prev1 = prev1->prev;
            token->prev->next = token->next;
            if (token->next)
                token->next->prev = token->prev;
            token->prev = prev1;
            if (prev1)
                token->next = prev1->next;
            else
                token->next = mini->start;
            if (!prev1)
                prev1 = token;
            prev1->next->prev = token;
            if (!mini->start->prev)
                prev1->next = token;
            if (mini->start->prev)
                mini->start = mini->start->prev;
        }
        token = token->next;
    }
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
    take_args(mini);//dopisat' //squish args
    token = mini->start;
    while (token)
    {
        if (is_type(token, 2))//check
            type_arg(token, 0);//dopisat' ..init_args 
        token = token->next;
    }
}


char *discovering(char *param, t_env *env, int err)
{
    
}