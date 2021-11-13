#include "libft.h"

int	ft_length_u(unsigned long n, int back, int base)
{
	int	length;

	length = 1;
	while (n / base != 0)
	{
		n = n / base;
		length++;
	}
	if (back > 2147483646)
		back = 2147483646;
	if (back > length)
		length = back;
	return (length);
}

char	*utoa_f(unsigned long n, int back, int flag, int base)
{
	int		i;
	int		length;
	char	*s1;

	i = 0;
	length = ft_length_u(n, back, base);
	if (n < 0 && flag)
		length++;
	s1 = malloc(length + 1);
	if (!s1)
		return (NULL);
	while (i < length)
		s1[i++] = '0';
	s1[length] = '\0';
	while (n / base != 0)
	{
		s1[--length] = "0123456789abcdef"[n % base];
		n = n / base;
	}
	s1[--length] = "0123456789abcdef"[n % base];
	return (s1);
}
