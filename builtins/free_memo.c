#include "../minishell.h"

void	*free_memo(void *s)
{
	if (s)
	{
		free(s);
		s = NULL;
	}
	return (NULL);
}