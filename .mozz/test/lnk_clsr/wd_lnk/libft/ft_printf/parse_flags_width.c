/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags_width.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:41:17 by gmentat           #+#    #+#             */
/*   Updated: 2020/01/06 23:15:34 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	hel_p_f_w_z(t_f_arg *w_f, char *flags, char type, va_list ap)
{
	if (w_f->width != NULL || (*flags != 46 && *flags != 42 &&
		*flags != 108 && *flags != 104 && *flags != type &&
		!(ft_isdigit(*(flags)))))
		w_f->exeptions = -1;
	w_f->i_width = va_arg(ap, int);
	if (w_f->i_width < 0)
	{
		w_f->i_width = w_f->i_width * (-1);
		w_f->minus = w_f->yes;
	}
	w_f->width = w_f->yes;
}

char		*helper_parse_flags_width(t_f_arg *width_flags, char *flags)
{
	width_flags->i_width = ft_atoi(flags);
	if (width_flags->i_width < 0)
		width_flags->i_width = width_flags->i_width * (-1);
	width_flags->temp = ft_itoa(width_flags->i_width);
	flags += ft_strlen(width_flags->temp);
	ft_strdel(&width_flags->temp);
	return (flags);
}

void		parse_flags_width(t_f_arg *w_f, char *flags, char type, va_list ap)
{
	while (*flags && *flags != 46)
	{
		if (ft_isdigit(*flags))
		{
			if (*flags != 48)
				flags = helper_parse_flags_width(w_f, flags);
			while (*flags && *flags != 46)
			{
				if (*flags == 48 || *flags == 42)
					break ;
				++flags;
			}
		}
		if (*flags == 42)
			hel_p_f_w_z(w_f, flags, type, ap);
		if (*flags && *flags != 46)
			++flags;
	}
}
