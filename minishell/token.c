#include "../minishell.h"

t_token *next(t_token *token, int i)
{
    if (token && i)
        token = token->next;
    while (token && token->type < 3)
        token = token->next;
    return (token);
}

t_token *prev(t_token *token, int i)
{
    if (token && i)
        token = token->prev;
    while (token && token->type < 3)
        token = token->prev;
    return (token);
}

t_token *next_ex(t_token *token, int i)
{
    if (token && i)
        token = token->next;
    while (token && token->type != 1)
    {
        token = token->next;
        if (token && token->type == 1 && token->prev == NULL)
            continue;
        else if (token && token->type == 1 && token->prev->type < 7)
            token = token->next;
    }
    return (token);
}