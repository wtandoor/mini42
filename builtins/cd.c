#include "../minishell.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <signal.h>
// #include <string.h>
// #include "../libft/libft.h"
// #include "../libft/get_next_line.h"

// void cmd_cd(char **arg, t_env *env)
// {
//     getcwd(arg, 5000);    
// }


// int main (int args, char **argv, char **env)
// {
//     char *cd;

//     cmd_cd(cd, env);
//     printf("%s", cd);
// }
t_env	*ft_lstnew_m(char *content)
{
	t_env	*lst;

	lst = malloc(sizeof(t_env));
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

void	ft_lstadd_back_m(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (lst)
	{
		if (*lst)
		{
			temp = ft_lstlast_m(*lst);
			temp->next = new;
		}
		else
			*lst = new;
	}
}


int main(int argc, char **argv, char **env)
{
    int i = 0;
    t_env *env1;
    t_env   *tmp;
    char *s;
    
    tmp = NULL;
    env1 = tmp;
    while (env[i])
    {
        tmp = ft_lstnew_m(env[i]);
        ft_lstadd_back_m(&env1, tmp);
        i++;
    }
    tmp = env1;
    while (tmp)
        printf("%s\n", tmp->value), tmp = tmp->next;
    
    return 0;
}