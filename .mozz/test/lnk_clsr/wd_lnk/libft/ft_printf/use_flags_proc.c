/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_flags_proc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmentat <gmentat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 21:39:23 by gmentat           #+#    #+#             */
/*   Updated: 2019/12/30 14:00:59 by gmentat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_arg		*helper_use_flags_proc(t_f_arg *s_f, t_arg *args, int j)
{
	s_f->width = ft_strnew(s_f->i_width - (int)ft_strlen(args->str_result));
	if (s_f->zero == NULL || s_f->point != NULL)
	{
		while (j < (s_f->i_width - (int)ft_strlen(args->str_result)))
		{
			s_f->width[j] = ' ';
			j++;
		}
		if (s_f->minus == NULL)
			args->str_result = ft_fundel(args->str_result, s_f->width, 1, 2);
		else
			args->str_result = ft_fundel(args->str_result, s_f->width, 0, 2);
	}
	else if (s_f->zero != NULL && s_f->point == NULL)
	{
		while (j < (s_f->i_width - (int)ft_strlen(args->str_result)))
		{
			s_f->width[j] = '0';
			j++;
		}
		args->str_result = ft_fundel(args->str_result, s_f->width, 1, 2);
	}
	return (args);
}

t_arg		*check_length_proc(t_arg *args, t_f_arg *struct_flugs)
{
	args->len = ft_strlen(args->str_result);
	if (struct_flugs->point != NULL && struct_flugs->i_point == 0 &&
		(*(args->str_result) == '0' && args->u.val == 0))
	{
		args->len = 0;
	}
	return (args);
}

char		*struct_flugs_length_proc(t_arg *args)
{
	args->str_result = ft_strnew(1);
	args->str_result[0] = '%';
	return (args->str_result);
}

t_f_arg		*struct_flugs_proc(t_f_arg *struct_flugs)
{
	struct_flugs->grill = NULL;
	struct_flugs->point = NULL;
	struct_flugs->plus = NULL;
	struct_flugs->spase = NULL;
	struct_flugs->grill = NULL;
	if (struct_flugs->zero != NULL && struct_flugs->minus != NULL)
		struct_flugs->zero = NULL;
	return (struct_flugs);
}

t_arg		*use_flags_proc(t_f_arg *s_f, t_arg *args)
{
	s_f = struct_flugs_proc(s_f);
	args->str_result = struct_flugs_length_proc(args);
	if (s_f->i_width > (int)ft_strlen(args->str_result))
		args = helper_use_flags_proc(s_f, args, 0);
	args = check_length_proc(args, s_f);
	return (args);
}
