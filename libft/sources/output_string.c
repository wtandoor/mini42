#include "../ft_printf.h"

static	int	function(char *temp, t_flags flags)
{
	int		length;
	char	*s1;

	length = 0;
	if (!flags.accuracy && flags.dot)
		s1 = ft_strdup("");
	else
	{
		if (flags.accuracy)
			s1 = ft_substr(temp, 0, flags.accuracy);
		else
			s1 = ft_substr(temp, 0, ft_strlen(temp));
	}
	if (!s1)
		return (-1);
	length = output_characters(s1, flags);
	free(s1);
	return (length);
}

int	output_string(t_flags flags, va_list parameters)
{
	char	*temp;
	int		length;
	int		flag;

	flag = 0;
	flag_edit(&flags, parameters);
	temp = va_arg(parameters, char *);
	if (!temp)
	{
		temp = ft_strdup("(null)");
		flag = 1;
	}
	length = function(temp, flags);
	if (flag)
		free(temp);
	return (length);
}
