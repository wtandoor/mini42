#include "../ft_printf.h"

int	width(char *s1, t_flags *flags)
{
	int	i;

	i = 0;
	if (s1[i] == '*')
	{
		flags->width = -1;
		i = 1;
	}
	else if (ft_isdigit(s1[i]))
	{
		while (ft_isdigit(s1[i]))
			i++;
		flags->width = ft_atoilen(s1, i);
	}
	return (i);
}

int	type_flags(char symb, t_flags flags)
{
	if (!ft_isdigit(symb) && symb != '*'
		&& symb != '.' && symb != '%'
		&& symb != 'd' && symb != 'i'
		&& symb != 'u' && symb != 'c'
		&& symb != 's' && symb != 'p'
		&& symb != 'x' && symb != 'X'
		&& symb != '-' && symb != ' ')
		return (0);
	if (flags.type != 0)
		return (0);
	return (1);
}
