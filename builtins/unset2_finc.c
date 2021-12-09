#include "../minishell.h"
void free_element(t_mini *mini, t_env *env)
{
    if (mini->env == env && env->next == NULL)
    {
        free_memo(mini->env->value);
        mini->env->value = NULL;
		mini->env->next = NULL;
		return ;
    }
    free_memo(env->value);
    free_memo(env);
}