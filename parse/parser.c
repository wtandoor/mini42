#include "../minishell.h"

char *ft_quote(char *str, int *i)
{
	int j;
	char *temp;
	char *temp2;
	char *temp3;

	j = *i;
	while (str[++(*i)])
		if(str[*i] == '\'')
			break;
	temp = ft_substr(str, 0, j);
	temp2 = ft_substr(str, j + 1, *i - j - 1);
	temp3 = ft_strdup(str + *i + 1);
	temp = ft_strjoin(temp, temp2);
	temp = ft_strjoin(temp, temp3);
	free(str);
	return (temp);
}

// char *ft_slash(char *str, int *i)
// {
//     int j;
//     char *temp;
//     char *temp2;
//     char *temp3;

//     j = *i;
//     while (str[++(*i)])
//         if (str[*i] == '\\')
//             break;
//     temp = ft_substr(str, 0, j);
//     temp2 = ft_substr(str, j + 1, *i - j - 1);
//     temp3 = ft_strdup(str + *i + 1);
//     temp = ft_strjoin(temp, temp2);
//     temp = ft_strjoin(temp, temp3);
//     free(str);
//     return (temp);
// }
int quotation(char *stroke, int m_int)
{
	int i;
	int available;

	i = 0;
	available = 0;
	while (stroke[i] && i != m_int)
	{
		if (i > 0 && stroke[i - 1] == '\\')
			;
		else if (available == 0 && stroke[i] == '\"')
			available = 1;
		else if (available == 0 && stroke[i] == '\'')
			available = 2;
		else if (available == 1 && stroke[i] == '\"')
			available = 0;
		else if (available == 2 && stroke[i] == '\'')
			available = 0;
		i++;
	}
	return (available);
}

int	checking_quotes(t_mini *mini, char **stroke)
{
	if (quotation(*stroke, MAX_INT))
	{
		ft_putendl_fd("minishell: syntax error with open quotes", STDERR);
		free_memo(*stroke);
		mini->ret = 2;
		mini->start = NULL;
	}
	return 0;
}

void parser(t_mini *mini) //>,>>, <, " " - текст без изменений(w/o $ \), ' ' , \ - след символ не служебный , $ , ; - разделяет команды , | - несколько команд
{
	char	*stroke;
	t_token	*tok;

	signal(SIGINT, &sigint);
	signal(SIGQUIT, &sigquit);
	if (mini->ret)
		ft_putstr_fd("error", STDERR);
	else
		ft_putstr_fd("^-^", STDERR);
	ft_putstr_fd("minishell ▸ ", STDERR);
	if (get_next_line(0, &stroke) == -2 && (mini->exit = 1))
		ft_putendl_fd("exit", STDERR);
	if (g_sig.sigint == 1)
		mini->ret = g_sig.exit_status;
	else 
		mini->ret = mini->ret;
	if (checking_quotes(mini, &stroke))
		return ;
	stroke = spacesof_lines(stroke);
	if (stroke && stroke[0] == '$')
		stroke[0] = (char)(-stroke[0]);
	// mini->start = tokens(stroke);
	printf("я прошел парсер\n");
	// i = -1;
	// while (str[++i])
	// {
	//     if (str[i] == '\'')
	//         str = ft_quote(str, &i);
	//     // if (str[i] == '\\')
	//     //     str = ft_slash(str, &i);
	// }
	// printf("str = %s", str);
}

