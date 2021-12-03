#include "../ft_printf.h"

int	output_decimal(t_flags flags, va_list parameters)
{
	int		nb;
	char	*s1;
	int		length;

	length = 0;
	flag_edit(&flags, parameters);
	nb = va_arg(parameters, int);
	if (flags.dot && !flags.accuracy && !nb)
		s1 = ft_strdup("");
	else
		s1 = string_edit_id(nb, flags);
	if (!s1)
		return (-1);
	length = output_characters(s1, flags);
	free(s1);
	return (length);
}

char	*search_space(int n, t_flags flags, char *s1, int flag)
{
	char	*Void;
	char	*s_edit;

	s_edit = "";
	Void = " ";
	if (n >= 0 && flags.space)
	{
		if (!flag)
		{
			s_edit = ft_strdup(s1);
			if (!s_edit)
				return (0);
			s_edit[0] = ' ';
		}
		else
		{
			s_edit = ft_strjoin(Void, s1);
			if (!s_edit)
				return (0);
		}
		free(s1);
		return (s_edit);
	}
	return (s1);
}

char	*string_edit_id(int nb, t_flags flags)
{
	int		flag;
	char	*s1;

	if (flags.zero && !flags.minus
		&& !flags.dot && flags.width && !flags.accuracy)
	{
		s1 = itoa_f(nb, flags.width, 0);
		flag = 0;
	}
	else
	{
		s1 = itoa_f(nb, flags.accuracy, 1);
		flag = 1;
	}
	if (!s1)
		return (0);
	s1 = search_space(nb, flags, s1, flag);
	return (s1);
}
