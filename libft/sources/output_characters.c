#include "ft_printf.h"

int	output_characters(char *s1, t_flags flags)
{
	int	length;
	int	l;

	length = 0;
	if (s1 == NULL)
		return (output_characters("(null)", flags));
	l = ft_strlen(s1);
	if (flags.minus)
		length = output_negative(s1, flags, l);
	else
		length = output_positive(s1, flags, l);
	return (length);
}

int	output_positive(char *s1, t_flags flags, int l)
{
	int	length;
	int	save_length;

	length = 0;
	flags.width = flags.width - l;
	while (flags.width > 0)
	{
		length += ft_putchar_fd(' ', 1);
		flags.width--;
	}
	save_length = length;
	length = 0;
	while (length < l)
		write(1, &s1[length++], 1);
	length = length + save_length;
	return (length);
}

int	output_negative(char *s1, t_flags flags, int l)
{
	int	length;

	length = 0;
	while (length < l)
	{
		write(1, &s1[length], 1);
		flags.width--;
		length++;
	}
	while (flags.width-- > 0)
		length = length + ft_putchar_fd(' ', 1);
	return (length);
}
