#include "../ft_printf.h"

char	*string_edit_u(unsigned int nb, t_flags flags)
{
	char	*s1;

	if (flags.zero && !flags.minus
		&& !flags.accuracy && !flags.dot && flags.width)
		s1 = utoa_f(nb, flags.width, 0, 10);
	else
		s1 = utoa_f(nb, flags.accuracy, 1, 10);
	if (!s1)
		return (0);
	return (s1);
}

int	output_unsigned(t_flags flags, va_list parameters)
{
	unsigned int	nb;
	char			*s1;
	int				length;

	length = 0;
	flag_edit(&flags, parameters);
	nb = va_arg(parameters, unsigned int);
	if (!flags.accuracy && flags.dot && !nb)
		s1 = ft_strdup("");
	else
		s1 = string_edit_u(nb, flags);
	if (!s1)
		return (-1);
	length = output_characters(s1, flags);
	free(s1);
	return (length);
}
