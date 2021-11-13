#include "ft_printf.h"

char	*string_edit_per(t_flags flags)
{
	char	*s1;

	if (flags.width && flags.zero)
	{
		s1 = malloc(1 * flags.width + 1);
		if (!s1)
			return (0);
		s1[flags.width] = '\0';
		s1[--flags.width] = '%';
		while (flags.width > 0)
			s1[--flags.width] = '0';
	}
	else
	{
		s1 = malloc(2);
		if (!s1)
			return (0);
		s1[0] = '%';
		s1[1] = '\0';
	}
	return (s1);
}

int	output_percentage(t_flags flags, va_list parameters)
{
	char	*s1;
	int		length;

	flag_edit(&flags, parameters);
	length = 0;
	s1 = string_edit_per(flags);
	if (!s1)
		return (-1);
	length = output_characters(s1, flags);
	free (s1);
	return (length);
}
