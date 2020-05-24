/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags_basic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:43:51 by gmentat           #+#    #+#             */
/*   Updated: 2020/01/06 23:15:51 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*parse_flags_basic_helper(t_f_arg *basic_flags, char *flags, int i)
{
	if (i < 0)
		i *= -1;
	basic_flags->temp = ft_itoa(i);
	flags += ft_strlen(basic_flags->temp);
	ft_strdel(&basic_flags->temp);
	return (flags);
}

void		parse_flags_basic(t_f_arg *basic_flags, char *flags, int i)
{
	while (*flags)
	{
		if (*flags == 43)
			basic_flags->plus = basic_flags->yes;
		else if (*flags == 45)
			basic_flags->minus = basic_flags->yes;
		else if (*flags == 35)
			basic_flags->grill = basic_flags->yes;
		else if (*flags == 32)
			basic_flags->spase = basic_flags->yes;
		else if (*flags == 46)
		{
			++flags;
			if (*flags == 48)
				++flags;
		}
		else if (*flags == 48)
			basic_flags->zero = basic_flags->yes;
		if ((i = ft_atoi(flags)) && *flags != 45 && *flags != 35 &&
		*flags != 43 && *flags != 32)
			flags = parse_flags_basic_helper(basic_flags, flags, i);
		else if (*flags)
			++flags;
	}
}
