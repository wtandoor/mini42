#include "ft_printf.h"

int	output(char *s1, va_list parameters)
{
	int		i;
	int		length;
	t_flags	flags;

	i = 0;
	length = 0;
	while (s1[i])
	{
		flags = flag_init();
		if (s1[i] == '%' && s1[i + 1])
		{
			i = i + search_flags(&flags, s1 + i + 1);
			length += string_flags(flags, parameters);
			if (length < 0)
				return (-1);
		}
		else if (s1[i] != '%')
			length += ft_putchar_fd(s1[i], 1);
		i++;
	}
	return (length);
}
