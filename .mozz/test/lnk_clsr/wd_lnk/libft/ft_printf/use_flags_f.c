/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_flags_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmentat <gmentat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 18:54:44 by gmentat           #+#    #+#             */
/*   Updated: 2019/12/30 14:01:01 by gmentat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		use_flags_h_f(t_arg *args)
{
	args->dup = ft_strnew((ft_strlen(args->str_result)) - 1);
	args->str_result++;
	ft_memmove(args->dup, args->str_result, (ft_strlen(args->str_result)));
	args->str_result--;
	ft_strdel(&args->str_result);
	args->str_result = ft_strnew(ft_strlen(args->dup));
	ft_memmove(args->str_result, args->dup, (ft_strlen(args->dup)));
	ft_strdel(&args->dup);
}

char		*struct_flugs_length_f(t_f_arg *s_f, t_arg *args, va_list ap)
{
	if (s_f->fl != NULL)
		args->u.val_ld = va_arg(ap, double);
	else if (s_f->fll != NULL)
		args->u.val_ld = va_arg(ap, long double);
	else
		args->u.val_ld = va_arg(ap, double);
	if (s_f->point == NULL)
		args->str_result = get_float(args->u.val_ld, 6);
	else
		args->str_result = get_float(args->u.val_ld, s_f->i_point);
	return (args->str_result);
}

t_f_arg		*struct_flugs_f(t_f_arg *s_f)
{
	if (s_f->zero != NULL && s_f->minus != NULL)
		s_f->zero = NULL;
	if (s_f->plus != NULL && s_f->spase != NULL)
		s_f->spase = NULL;
	return (s_f);
}

t_arg		*use_flags_f(t_f_arg *s_f, t_arg *args, va_list ap)
{
	args->str_result = struct_flugs_length_f(s_f, args, ap);
	if (s_f->grill != NULL && ft_strchr(args->str_result, '.') == NULL)
		args->str_result = ft_fundel(args->str_result, ".", 2, 0);
	if (*(args->str_result) == '-')
	{
		use_flags_h_f(args);
		s_f->less_zero = s_f->yes;
	}
	s_f = struct_flugs_f(s_f);
	if ((s_f->less_zero != NULL && s_f->zero == NULL) ||
		(s_f->less_zero != NULL && (s_f->zero != NULL &&
		s_f->i_width <= (int)ft_strlen(args->str_result))))
		args->str_result = ft_fundel(args->str_result, "-", 2, 1);
	else if ((s_f->zero == NULL || (s_f->point != NULL && args->type != 'f') ||
		(s_f->i_width <= (int)ft_strlen(args->str_result))) &&
		s_f->plus != NULL)
		args->str_result = ft_fundel(args->str_result, "+", 2, 1);
	else if ((s_f->spase != NULL && s_f->zero == NULL) ||
		(s_f->spase != NULL && s_f->zero != NULL &&
		s_f->i_width <= (int)ft_strlen(args->str_result)))
		args->str_result = ft_fundel(args->str_result, " ", 2, 1);
	if (s_f->i_width > (int)ft_strlen(args->str_result))
		args = use_mod_width(s_f, args, 0);
	args->len = ft_strlen(args->str_result);
	return (args);
}
