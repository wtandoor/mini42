#include "../minishell.c"

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