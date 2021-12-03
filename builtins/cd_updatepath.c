#include "../minishell.h"

///ДЛЯ ПРОВЕРКИ EXPORTа
// int init_sec_env(t_mini *mini, char **env_ar)
// {
//     t_env *env;
//     t_env *new1;
//     int i;

//     env = (t_env *)malloc(sizeof(t_env));
//     if (!env)
//         return (1);
//     env->value = ft_strdup(env_ar[0]);
//     env->next = NULL;
//     mini->sec_env = env;
//     i = 1;
//     while (env_ar && env_ar[0] && env_ar[i])
//     {
//         new1 = (t_env *)malloc(sizeof(t_env));
//         if (!new1)
//             return (1);
//         new1->value = ft_strdup(env_ar[i]);
//         new1->next = NULL;
//         env->next = new1;
//         env = new1;
//         i++;
//     }
//     return (0);
// }


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
			printf("env->value before  :%s\n", env->value);
			env->value = ft_strdup(old_path);
			printf("env->value after :%s\n", env->value);
			
			return (1);
		}
		// printf("%d IN FUNC: %s\n\n", i, env->value);
		env = env->next;
	}
	
	return (0);
}

int	add_env(char *path, t_env *env)			//добавляет OLDPWD, если в предидущей он не нашелся
{
	t_env *temp;
	t_env *usable;

	printf("patht: %s\n", path);
	if (env && env->value == NULL)
	{
		env->value = ft_strdup(path);
		return (0);
	}
	usable = (t_env *)malloc(sizeof(t_env));
	if (!usable)
		return (-1);
	usable->value = ft_strdup(path); 
	while (env && env->next && env->next->next)
	{
		printf("%s\n", env->value);
		env = env->next;
	}

	temp = env->next;
	env->next = usable;
	// printf("temp: %s\n", temp->value);
	// printf("after: env->next: %s\n", usable->value);
	usable->next = temp;
	return (0);
}


int update_old_path(t_env *env)
{
	char *cwd;
	char *old_path;

	cwd = (char *)malloc(sizeof (char *) * 50000);
	getcwd(cwd, PATH);
	if (cwd == NULL)
		return (ERROR);
	old_path = ft_strjoin("OLDPWD=", cwd); //записал место, где мы находимся сейчас
	// printf(" old_path____: %s\n", old_path);
	if (!old_path)
		return (ERROR);
	if (find_env(old_path, env) == 0) //если программа завершилась успешно, перед этим мы в oldpath добавили дирректорию, которая будет устаревшей при следующем  переходе
		add_env(old_path, env); //функция добавляет oldpwd сам если не нашел ее в исходнике////НО ОНА ВСТАВЛЯЕТ НЕВЕРНЫЙ ПУТЬ
	// printf("напечатай мне что выведетfind_env: %i\n", find_env(old_path, env));
	// printf("%s\n\n", old_path);
	free_memo(old_path);
	return (SUCCESS);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////////////////////
static char		*path_of_env(t_env *env, const char *var, size_t len) //функция ищет путь, который мы задаем. потом она его пихает в какую-то переменную
{
	char *path;
	int	i;
	int length;
	int	h;

	i = 0;
	h = 0;
	while (env && env->next)
	{
		if (!ft_strncmp(env->value, var, len))
		{
			length = ft_strlen(env->value) - len;
			path = (char *)malloc(sizeof(char *) * length + 1);
			if (!path)
				return (NULL);
			while (env->value[i])
			{
				if(i > (int)len)
				{
					path[h] = env->value[i];
					h++;
					// printf("%s\n", path);
				}
				i++;
			}
			path[h] = '\0';
			printf("%s\n", path);
			return (path);
		}
		env = env->next;
	}
	return (NULL);
}

int go_find_p_env(int variation, t_env *env)
{
	char *path;

	path = NULL;
	if (variation == 0)
	{
		path = path_of_env(env, "HOME", 4);// хероботина определяет путь home
		if (!path)
			ft_putendl_fd("HOME is missing", 2);
		if (!path)
			return (ERROR);
	}
	if (variation == 1) 
		path = path_of_env(env, "OLDPWD", 6);
		if (!path)
		{
			ft_putendl_fd("OLDPWD is missing", 2);
		}
		if (!path)
			return (ERROR);
		free_memo(path);
	return (1);

}

int ft_cd(char **strs, t_env *env)
{
	int cd_val;

	if (!strs)
		return (go_find_p_env(0, env));
	if (ft_strcmp(strs[1], "-") == 0)
		cd_val = go_find_p_env(1, env);
	else
	{
		update_old_path(env);
		cd_val = chdir(strs[1]);
		if (cd_val < 0)
			cd_val = cd_val * (-1);
		if (cd_val != 0)
			error(strs);
	}
	return (1);
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
    // while (env1 && env1->next)
	// {
	// 	printf("%s\n", env1->value);
	// 	env1 = env1->next;
	// }

	// ft_cd(0, env1);
    return (0);
}