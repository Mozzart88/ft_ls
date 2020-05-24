/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_flags_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmentat <gmentat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:44:48 by gmentat           #+#    #+#             */
/*   Updated: 2019/12/30 14:00:57 by gmentat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_arg		*helper_use_flags_s(t_f_arg *st_f, t_arg *a, int j)
{
	st_f->width = ft_strnew(st_f->i_width - (int)ft_strlen(a->str_result));
	while (j < (st_f->i_width - (int)ft_strlen(a->str_result)))
	{
		st_f->width[j] = ' ';
		j++;
	}
	if (st_f->minus == NULL)
		a->str_result = ft_fundel(a->str_result, st_f->width, 1, 2);
	else
		a->str_result = ft_fundel(a->str_result, st_f->width, 0, 2);
	if (st_f->zero != NULL && (st_f->minus == NULL || st_f->point == NULL))
		ft_memset(a->str_result, '0', j);
	return (a);
}

t_arg		*check_length_s(t_arg *args, t_f_arg *struct_flugs)
{
	args->len = ft_strlen(args->str_result);
	if (struct_flugs->point != NULL && struct_flugs->i_point == 0 &&
		(*(args->str_result) == '0' && args->u.val == 0))
	{
		args->len = 0;
	}
	return (args);
}

char		*struct_flugs_length_s(t_arg *args, va_list ap)
{
	args->s_str = va_arg(ap, char*);
	if (args->s_str == NULL)
	{
		args->s_str = "(null)";
	}
	return (args->s_str);
}

t_f_arg		*struct_flugs_s(t_f_arg *struct_flugs)
{
	struct_flugs->plus = NULL;
	struct_flugs->spase = NULL;
	struct_flugs->grill = NULL;
	if (struct_flugs->zero != NULL && struct_flugs->point != NULL)
		struct_flugs->zero = NULL;
	if (struct_flugs->zero != NULL && struct_flugs->minus != NULL)
		struct_flugs->zero = NULL;
	return (struct_flugs);
}

t_arg		*use_flags_s(t_f_arg *st_f, t_arg *a, va_list ap)
{
	int j;

	j = 0;
	st_f = struct_flugs_s(st_f);
	a->s_str = struct_flugs_length_s(a, ap);
	if (st_f->point != NULL && (st_f->i_point < (int)ft_strlen(a->s_str)))
	{
		a->str_result = ft_strnew(ft_strlen(a->s_str));
		a->str_result = ft_memmove(a->str_result, a->s_str, st_f->i_point);
	}
	else
	{
		j = ft_strlen(a->s_str);
		a->str_result = ft_strnew(ft_strlen(a->s_str));
		a->str_result = ft_memmove(a->str_result, a->s_str, j);
	}
	a->s_str = NULL;
	if (st_f->i_width > (int)ft_strlen(a->str_result))
		a = helper_use_flags_s(st_f, a, 0);
	a = check_length_s(a, st_f);
	return (a);
}
