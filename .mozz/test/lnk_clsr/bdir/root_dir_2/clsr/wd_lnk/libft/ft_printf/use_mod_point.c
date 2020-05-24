/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_mod_point.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:00:13 by gmentat           #+#    #+#             */
/*   Updated: 2020/01/07 15:25:23 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	use_mod_point(t_f_arg *s_f, t_arg *args)
{
	int j;
	int l;
	int rl;

	j = 0;
	s_f->point = NULL;
	rl = (int)ft_strlen(args->str_result);
	l = s_f->i_point - rl;
	s_f->point = ft_strnew(l + rl);
	while (j < l)
	{
		s_f->point[j] = 48;
		++j;
	}
	ft_strcpy(s_f->point + l, args->str_result);
	ft_strdel(&args->str_result);
	args->str_result = s_f->point;
	s_f->point = NULL;
}
