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
		return (SUCCESS);
	if (ft_strncmp(strs[1], env->value, len_env_value_static(env->value)) == 0)
	{
		if (env->next)
			mini->env = env->next;
		else 
			mini->env = mini->env;
		free_element(mini, env);
		return (SUCCESS);
	}
	while (env && env->next)
	{
		// printf("unset :%s\n", env->value);
		if (ft_strncmp(strs[1], env->next->value, len_env_value_static(env->next->value)) == 0)
		{
			temp = env->next->next;
			free_element(mini, env->next);
			env->next = temp;
			return (SUCCESS);
		}
		env = env->next;
	}
	// while (mini->env)
	// 	{
	// 		printf("unset _ %s\n", mini->env->value);
	// 		mini->env = mini->env->next;
	// 	}
	return (SUCCESS);
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
