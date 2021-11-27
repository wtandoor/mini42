#include "../includes/minishell.h"





void execute_command(t_mini *mini, t_token *token)
{
    char    **command;
    int     i;

    // if (mini->charge == 0)
    //     return ;
    i = 0;
    command = create_tab(token);
    while (command && command[i])
        command[i] = discovering(command[i++], mini->env, mini->ret);
    
    
}