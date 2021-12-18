#include "../minishell.h"

char	*space_alloc(char *line)
{
	char	*new1;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (separation(line, i))
			count++;
		i++;
	}
	if (!(new1 = (char *)malloc(sizeof(char) * (i + 2 * count + 1))))
		return (NULL);
	return (new1);
}

char	*space_line(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = space_alloc(line);
	while (new && line[i])
	{
		if (quote(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
			new[j++] = (char)(-line[i++]);
		else if (quote(line, i) == 0 && separation(line, i))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quote(line, i) == 0 && line[i] == '>')
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	free_memo(line);
	return (new);
}

char	*get_var_value(const char *arg, int pos, t_env *env, int ret)
{
	char	var_name[4096];
	char	*var_value;
	int		i;

	i = 0;
	if (arg[pos] == '?')
	{
		var_value = ft_itoa(ret);
		return (var_value);
	}
	if (ft_isdigit(arg[pos]))
		return (NULL);
	while (arg[pos] && env_char(arg[pos]) == 1 && i < 4096)
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = get_env_val(var_name, env);
	return (var_value);
}
