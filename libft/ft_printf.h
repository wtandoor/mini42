/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:56:06 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/18 17:29:38 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

typedef struct s_flags
{
	int	type;
	int	width;
	int	minus;
	int	zero;
	int	accuracy;
	int	space;
	int	dot;
}					t_flags;

int		ft_printf(const char *s, ...);
int		output(char *s1, va_list parameters);
int		search_flags(t_flags *flags, char *s1);
int		string_flags(t_flags flags, va_list parameters);
int		zero(char symb, t_flags *flags);
int		minus(char symb, t_flags *flags);
int		void_2(char symb, t_flags *flags);
int		dot(char symb, t_flags *flags);
int		accuracy(char *s1, t_flags *flags);
int		width(char *s1, t_flags *flags);
int		type_flags(char symb, t_flags flags);
int		output_negative(char *s1, t_flags flgas, int l);
int		output_positive(char *s1, t_flags flags, int l);
int		output_characters(char *s1, t_flags flags);
int		output_decimal(t_flags flags, va_list parameters);
int		output_unsigned(t_flags flgas, va_list parameters);
int		output_string(t_flags, va_list parameters);
int		output_char(t_flags flags, va_list parameters);
int		output_char_negative(char symb, t_flags flags);
int		output_char_positive(char symb, t_flags flags);
int		c_null(char symb, t_flags flags);
int		output_sixteen(t_flags flags, va_list parameters);
int		output_p(t_flags flags, va_list parameters);
int		output_percentage(t_flags flags, va_list parameters);
char	*string_edit_p(unsigned long nb, t_flags flags);
char	*string_edit_six(unsigned int nb, t_flags flags);
char	*string_edit_id(int nb, t_flags flags);
char	*search_space(int n, t_flags flags, char *s1, int flag);
char	*string_edit_u(unsigned int nb, t_flags flags);

void	flag_edit(t_flags *flags, va_list parameters);

t_flags	flag_init(void);

#endif
