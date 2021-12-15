/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtandoor <wtandoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:55:06 by wtandoor          #+#    #+#             */
/*   Updated: 2021/12/15 14:55:07 by wtandoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

t_flags	flag_init(void)
{
	t_flags	flags;

	flags.width = 0;
	flags.minus = 0;
	flags.type = 0;
	flags.accuracy = 0;
	flags.space = 0;
	flags.dot = 0;
	flags.zero = 0;
	return (flags);
}
