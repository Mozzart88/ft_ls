/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_flags_d_i.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:15:25 by gmentat           #+#    #+#             */
/*   Updated: 2020/01/07 15:22:32 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		use_flags_h_d_i(t_arg *args)
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

void		check_length_d_i(t_arg *args, t_f_arg *struct_flugs)
{
	args->len = ft_strlen(args->str_result);
	if (struct_flugs->point != NULL && struct_flugs->i_point == 0 &&
		(*(args->str_result) == '0' && args->u.val == 0))
		args->len = args->len + 1;
}

static void	struct_flugs_d_i(t_f_arg *struct_flugs)
{
	struct_flugs->grill = NULL;
	if (struct_flugs->zero != NULL && struct_flugs->point != NULL)
		struct_flugs->zero = NULL;
	if (struct_flugs->zero != NULL && struct_flugs->minus != NULL)
		struct_flugs->zero = NULL;
	if (struct_flugs->plus != NULL && struct_flugs->spase != NULL)
		struct_flugs->spase = NULL;
}

void		use_flags_d_i(t_f_arg *s_f, t_arg *args, va_list ap)
{
	struct_flugs_d_i(s_f);
	struct_flugs_length_d_i(s_f, args, ap);
	if (*(args->str_result) == '-')
	{
		use_flags_h_d_i(args);
		s_f->less_zero = s_f->yes;
	}
	if (s_f->i_point > (int)ft_strlen(args->str_result))
		use_mod_point(s_f, args);
	if ((s_f->less_zero != NULL && s_f->zero == NULL) ||
		(s_f->less_zero != NULL && (s_f->zero != NULL &&
		s_f->i_width <= (int)ft_strlen(args->str_result))))
		args->str_result = ft_fundel(args->str_result, "-", 2, 1);
	else if ((s_f->zero == NULL || s_f->point != NULL ||
		(s_f->i_width <= (int)ft_strlen(args->str_result))) &&
		s_f->plus != NULL)
		args->str_result = ft_fundel(args->str_result, "+", 2, 1);
	else if ((s_f->zero == NULL || (s_f->zero != NULL &&
		s_f->i_width <= (int)ft_strlen(args->str_result)) ||
		s_f->point != NULL) && s_f->spase != NULL)
		args->str_result = ft_fundel(args->str_result, " ", 2, 1);
	if (s_f->i_width > (int)ft_strlen(args->str_result))
		args = use_mod_width(s_f, args, 0);
	check_length_d_i(args, s_f);
}
