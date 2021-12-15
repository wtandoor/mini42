#include "../minishell.h"


/* для компиляции МАШЕ:::::
gcc libft/libft.a builtins/*.c env/*.c main_bleat/main_bleat1.c minishell.c minishell.h && ./a.out
 */
                                                                    // общий main

// int main(int argc, char **argv, char **env)
// {
// 	t_mini mini;

// 	(void)argc;
// 	(void)argv;
// 	init_mini(&mini);
// 	init_fds(&mini);
// 	init_env(&mini, env);
// 	init_sec_env(&mini, env);
// 	update_shell_lvl(mini.env);
// 	// while(mini.env)
//     // {
//     //     printf("%s\n", mini.env->value);
//     //     mini.env = mini.env->next;
//     // }
// 	while (mini.exit == 0)
// 	{
// 		init_sig();
// 		parser(&mini);
// 		// if (mini.start != NULL && line_check(&mini, mini.start))
// 		// 	mshell(&mini);
// 		// free_token(mini.start);
// 	}
// 	// free_env(mini.env);
// 	// free_env(mini.sec_env);
// 	// return(mini.ret);
// }

                                                                    /* cd */
// int main (int args, char **argv, char **env)
// {
//     char *cd;

//     cmd_cd(cd, env);
//     printf("%s", cd);
// }

// int main(int argc, char **argv, char **env)
// {
//     int i = 0;
//     t_env *env1;
//     t_env   *tmp;
    
// 	(void)argc;
// 	(void)argv;
//     tmp = NULL;
//     env1 = tmp;
//     while (env[i])
//     {
//         tmp = ft_lstnew_m(env[i]);
//         ft_lstadd_back_m(&env1, tmp);
//         i++;
//     }
//     tmp = env1;
//     while (tmp)
//         printf("%s\n", tmp->value), tmp = tmp->next;
    
//     return 0;
// }


                                                                    // unset 


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
	strs = (char **)malloc(sizeof(char *) * 3);
	strs[0] = ft_strdup("export");
	strs[1] = ft_strdup("as=as");
	strs[2] = NULL;
	ft_export(strs, mini.env, mini.sec_env);
	strs[0] = ft_strdup("unset");
	strs[1] = ft_strdup("as=as");
	ft_unset(strs, &mini); ////не удаляет значение export
	// while (mini.env && mini.env->next)
	// {
	// 	printf("unset after _ %s\n", mini.env->value);
	// 	mini.env = mini.env->next;
	// }
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

                                                                    // cd_updatepath

// int main(int argc, char **argv, char **env)
// {
//     int i = 0;
//     t_env *env1;
//     t_env   *tmp;
//     char *s;
    
//     tmp = NULL;
//     env1 = tmp;
//     while (env[i])
//     {
//         tmp = ft_lstnew_m(env[i]);
//         ft_lstadd_back_m(&env1, tmp);
//         i++;
//     }
//     tmp = env1;
//     // while (env1)
//         // printf("%s\n", env1->value), env1 = env1->next;
// 	update_old_path(env1);
//     // while (env1 && env1->next)
// 	// {
// 	// 	printf("%s\n", env1->value);
// 	// 	env1 = env1->next;
// 	// }

// 	// ft_cd(0, env1);
//     return (0);
// }