#include "../minishell.h"
int separation(char *buff, int i)
{
    if (i > 0 && buff[i - 1] && ft_strchr("<>|;", buff[i]))
        return (0);
    else if (ft_strchr("<>|;", buff[i]) && quotation(buff, i) == 0)
        return (1);
    else
        return (0);
}

char *malloc_buff(char *buff)
{
    char *new_buff;
    int i;
    int j;

    i = 0;
    j = 0;
    while (buff[i])
    {
        if (separation(buff, i))
            j++;
        i++;
    }
    new_buff = (char *)malloc(sizeof(char) * (i + 2 * j + 1));
    if(!new_buff)
        return (NULL);
    return(new_buff);
}

char *spacesof_lines(char *line)
{
    char *buff;
    int i;
    int j;

    buff = malloc_buff(line);
    while (buff && line[i])
    {
        if (quotation(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
            buff[j++] = (char)(-line[i++]);
        else if (quotation(line, i) == 0 && separation(line, i))
        {
            buff[j++] = ' ';
            buff[j++] = line[i++];
            if (quotation(line, i) == 0 && line[i] == '>')
                buff[j++] = line[i++];
            buff[j++] = ' ';
        }
        else
            buff[j++] = line[i++];
    }
    buff[j] = '\0';
    free_memo(line);
    return (buff);
}