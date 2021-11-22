#include "../includes/minishell.h"

////finds the path////
char *name_of_env(char *to, char *from)
{
	int i;

	i = 0;
	while (from[i] && from[i] != '=')
	{
		to[i] = from[i];
		i++;
	}
	to[i] = '\0';
	return (to);
}

///compares oldENV with the new one////
int find_env(char *old_path, t_env *env)
{
	char old_one[PATH];
	char new_one[PATH];

	name_of_env(old_one, old_path);//finds the name of path
	while (env && env->next)
	{
		name_of_env(new_one, env->value);//bring the path of enviroments and put them to new_one var
		if (ft_strcmp(old_one, new_one) == 0)
		{
			// free_memo(env->value);///------------------FAIL!!!!!!!!!!!!!!!!!!!!!!!!
			printf("2) old_one :%s\n", env->value);
			env->value = ft_strdup(old_path);
			return (1);
		}
		env = env->next;
	}
	return 0;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////
int	ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*str;
	char	*tmp;

	len = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	tmp = str;
	while (len--)
		*str++ = *s1++;
	*str = '\0';
	return (tmp);
}


int	ft_strlen(const char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		s++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*dest;
	unsigned int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	dest = (char*)malloc(sizeof(*dest) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	while (*s1 != '\0')
		dest[i++] = *s1++;
	while (*s2 != '\0')
		dest[i++] = *s2++;
	dest[i] = '\0';
	return (dest);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////












int update_old_path(t_env *env)
{
	char *cwd;
	char *old_path;

	cwd = (char *)malloc(sizeof (char *) * 5000);
	getcwd(cwd, PATH);
	if (cwd == NULL)
		return (ERROR);
	old_path = ft_strjoin("OLDPWD=", cwd); //записал место, где мы находимся сейчас
	printf(" old_path____: %s\n", old_path);
	if (!old_path)
		return (ERROR);
	if (find_env(old_path, env) == 0); //если программа завершилась успешно, перед этим мы в oldpath добавили дирректорию, которая будет устаревшей при следующем  переходе
		add_env(old_path, env);
	return (41);
}


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
    // while (env1)
        // printf("%s\n", env1->value), env1 = env1->next;
	update_old_path(env1);
    
    return 0;
}