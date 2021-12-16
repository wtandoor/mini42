#include "../minishell.h"

void	free_token(t_token *start)
{
	while (start && start->next)
	{
		free_memo(start->str);
		start = start->next;
		free_memo(start->prev);
	}
	if (start)
	{
		free_memo(start->str);
		free_memo(start);
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env && env->next)
	{
		tmp = env;
		env = env->next;
		free_memo(tmp->value);
		free_memo(tmp);
	}
	free_memo(env->value);
	free_memo(env);
}

void	*delete_memmory(void *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (NULL);
}