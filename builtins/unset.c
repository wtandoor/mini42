#include "../minishell.h"

static int len_env_value_static(char *env)
{
    int i;

    i = 0;
    while (env[i] && env[i] != '=')
        i++;
    return(i);
}

int ft_unset(char **strs, t_mini *mini)
{
	t_env *env;
	t_env *temp;

	env = mini->env;
	if (!(strs[1]))
		return (0);
	if (ft_strncmp(strs[1], env->value, len_env_value_static(env->value)) == 0)
	{
		if (env->next)
			mini->env = env->next;
		else 
			mini->env = mini->env;
		free_element(mini, env);
		return (0);
	}
	while (env && env->next)
	{
		if (ft_strncmp(strs[1], env->next->value, len_env_value_static(env->next->value)) == 0)
		{
			temp = env->next->next;
			free_element(mini, env->next);
			env->next = temp;
			return (0);
		}
		env = env->next;
	}
	return (0);
}

t_env	*ft_lstnew_m(char *content)
{
	t_env	*lst;

	lst = (t_env *)malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	lst->value = content;
	lst->next = NULL;
	return (lst);
}

t_env	*ft_lstlast_m(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_m(t_env **lst, t_env *new1)
{
	t_env	*temp;

	if (lst)
	{
		if (*lst)
		{
			temp = ft_lstlast_m(*lst);
			temp->next = new1;
		}
		else
			*lst = new1;
	}
}
