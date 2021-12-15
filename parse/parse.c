#include "../minishell.h"

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
    str = str_new(str);//check //ЧТО ЭТО?!
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

int copy_var(char *new, char *env_val, int pos)
{
    int i;

    i = 0;
    while (env_val[i])
        new[pos++] = env_val[i++];
    return (i);
}

void var_in(t_disc *str, char *param, t_env *env, int err)
{
    char *env_val;

    env_val = var_value(param, str->j, env, err);///get_var_value
    if (env_val)
        str->i += copy_var(str->new, env_val, str->i);//varlcpy //complete
    else
        str->i += 0;
    delete_memmory(env_val);
    if (ft_isdigit(param[str->j]) == 0 && param[str->j - 1] != '?')
        while(is_char(param[str->j]) == 1)//is_env_char
            str->j++;
    else
        if (param[str->j - 1] != '?')
            str->j++;
}

int res_size(int ret)
{
    char *temp;
    int len;

    temp = ft_itoa(ret);
    len = ft_strlen(temp);
    delete_memmory(temp);
    return(len);
}

int get_length(char *param, int i, t_env *env, int ret)
{
    char name_var[4096];
    char *var_value;
    int l;

    l = 0;
    if (param[i] == '?')
        return (res_size(ret)); //ret_size //comp
    if (ft_isdigit(param[i]))
        return (0);
    while (param[i] && is_char(param[i]) == 1 && i < 4096)
    {
        name_var[l] = param[i];
        i++;
        l++;
    }
    name_var[l] = '\0';
    var_value = get_env_val(name_var, env); //get_env_val //comp
    l = ft_strlen(var_value);
    delete_memmory(var_value);
    return (l);
}

int param_malloc(char *param, t_env *env, int err)
{
    int i;
    int size;

    i = -1;
    size = 0;
    while (param[++i])
    {
        if (param[i] == -36)
        {
            i++;
            if ((param[i] == '\0' || ft_isalnum(param[i]) == 0) && param[i] != '?')
                size++;
            else
                size += get_length(param, i, env, err); //get_var_len //comp
            if (ft_isdigit(param[i]) == 0)
            {
                while (param[i + 1] && is_char(param[i]))
                    i++;
            }
            else
                size--;
        }
        size++;
    }
    return (size);
}

int		is_char(int c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}

char *discovering(char *param, t_env *env, int err)
{
    t_disc str;
    int new_len;

    new_len = param_malloc(param, env, err); ///arg_alloc_len
    str.new = (char *)malloc(sizeof(char) * new_len + 1);
    if (!str.new)
        return (NULL);
    str.i = 0;
    str.j = 0;
    while (str.i < new_len && param[str.j])
    {
        while(param[str.j] == -36)
        {
            str.j++;
            if ((param[str.j] == '\0' || ft_isalnum(param[str.j]) == 0) && param[str.j] != '?')
                str.new[str.i++] = '$';
            else
                var_in(&str, param, env, err);
        }
        str.new[str.i++] = param[str.j++];
    }
    str.new[str.i] = '\0';
    return (str.new);
}