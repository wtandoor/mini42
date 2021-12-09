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
	printf("%s", mini->env->value);
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
		if (ft_strncmp(strs[1], env->next->value, len_env_value_static(env->next->value)) == 0)
		{
			temp = env->next->next;
			free_element(mini, env->next);
			env->next = temp;
			return (SUCCESS);
		}
		env = env->next;
	}
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

void init_mini(t_mini *mini)
{
    mini->in = dup(STDIN);
    mini->out = dup(STDOUT);
    mini->exit = 0;
    mini->ret = 0;
    mini->no_exec = 0;
}

int main(int argc, char **argv, char **env)
{
	int i = 0;
	t_env	*env1;
	t_env	*tmp;
	char	*s;
	t_mini	mini;
	char **strs;
	
	tmp = NULL;
	env1 = tmp;
	// while (env[i])
	// {
	// 	tmp = ft_lstnew_m(env[i]);
	// 	ft_lstadd_back_m(&env1, tmp);
	// 	i++;
	// }
	// tmp = env1;
	// while (env1)
	// 	printf("%s\n", env1->value), env1 = env1->next;
	init_mini(&mini);
	init_env(&mini, env);
	init_sec_env(&mini, env);
	printf("mini");
	strs = (char **)malloc(sizeof(char *) * 3);
	strs[0] = ft_strdup("asdasdasd");
	strs[1] = ft_strdup("secarg");
	strs[2] = NULL;
	
	// ft_export(strs, env1, mini.sec_env);
	
	ft_unset(strs, &mini);
	// printf("\n%s\n", mini.sec_env->value);
	// while (mini.sec_env->next)
	// {
	// 	printf("1) %s\n", mini.sec_env->value);
	// 	mini.sec_env = mini.sec_env->next;
	// }
	// printf("hello");
	// while (mini->sec_env)
	// 	printf("%s\n", mini->sec_env->value), mini->sec_env = mini->sec_env->next;
	// update_old_path(env1);
	// while (env1 && env1->next)
	// {
	// 	printf("%s\n", env1->value);
	// 	env1 = env1->next;
	// }

	// ft_cd(0, env1);
	return (0);
}