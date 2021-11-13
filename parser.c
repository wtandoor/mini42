#include "minishell.h"

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

void parser(char *str) //>,>>, <, " " - текст без изменений(w/o $ \), ' ' , \ - след символ не служебный , $ , ; - разделяет команды , | - несколько команд
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (str[i] == '\'')
            str = ft_quote(str, &i);
        // if (str[i] == '\\')
        //     str = ft_slash(str, &i);
    }
    printf("str = %s", str);
}

