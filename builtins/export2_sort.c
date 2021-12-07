#include "../minishell.h"
// int len_of_env(char **buff)
// {
// 	int i;

// 	i = 0;
// 	while (buff[i])
// 		i++;
// 	return (i);
// }

// void sort_buff(char **buff, int len)
// {
// 	char *temp;
// 	int	con;
// 	int	i;

// 	// printf("wannal = %s", buff[1]);
// 	i = 0;
// 	con = 0;
// 	while (buff && con == 0)
// 	{
// 		con = 1;
// 		i = 0;
// 		while (i < len - 1)
// 		{
// 			if (ft_strcmp(buff[i], buff[i + 1]) > 0)
// 			{
// 				temp = buff[i];
// 				buff[i] = buff[i + 1];
// 				buff[i + 1] = temp;
// 				con = 0;
// 			}
// 			i++;
// 		}
// 		len--;
		
// 	}
// 	int j = 0;
// 	// while (buff[j])
// 	// 		printf("%s\n", buff[j]), j++;
// }



int			str_env_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	sort_env1(char **tab, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	while (tab && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}
