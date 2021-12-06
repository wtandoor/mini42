#include "../ft_printf.h"

int	output_sixteen(t_flags flags, va_list parameters)
{
	unsigned int	nb;
	int				length;
	char			*s1;

	length = 0;
	flag_edit(&flags, parameters);
	nb = va_arg(parameters, unsigned int);
	if (!flags.accuracy && flags.dot && !nb)
		s1 = ft_strdup("");
	else
		s1 = string_edit_six(nb, flags);
	if (!s1)
		return (-1);
	nb = 0;
	while (s1[nb] && flags.type == 'X')
	{
		s1[nb] = ft_toupper(s1[nb]);
		nb++;
	}
	length = length + output_characters(s1, flags);
	free(s1);
	return (length);
}

char	*string_edit_six(unsigned int nb, t_flags flags)
{
	char	*s1;

	if (!flags.dot && flags.zero && !flags.minus
		&& !flags.accuracy && flags.width)
		s1 = utoa_f(nb, flags.width, 0, 16);
	else
		s1 = utoa_f(nb, flags.accuracy, 1, 16);
	if (!s1)
		return (0);
	return (s1);
}
