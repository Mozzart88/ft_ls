/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags_point.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:36:06 by gmentat           #+#    #+#             */
/*   Updated: 2020/01/06 23:16:02 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	helper_parse_flags_point(t_f_arg *p_fl, char type, va_list ap)
{
	++p_fl->point;
	if (*p_fl->point == 48)
		++p_fl->point;
	p_fl->i_point = ft_atoi(p_fl->point);
	if (p_fl->i_point)
	{
		p_fl->temp = ft_itoa(ft_atoi(p_fl->point));
		p_fl->point = p_fl->point + ft_strlen(p_fl->temp);
		ft_strdel(&p_fl->temp);
	}
	else if (*p_fl->point == 42)
	{
		p_fl->i_point = va_arg(ap, int);
		p_fl->point++;
	}
	else if (*(p_fl->point) == 48)
		++p_fl->point;
	while (p_fl->point)
	{
		if (*(p_fl->point) == type)
			break ;
		p_fl->point++;
	}
}

void		parse_flags_point(t_f_arg *p, char *flags, char type, va_list ap)
{
	if (!(p->point = ft_strchr(flags, 46)))
		return ;
	helper_parse_flags_point(p, type, ap);
	p->point = p->yes;
	if (p->i_point < 0)
	{
		p->i_point = 0;
		p->point = NULL;
	}
}
