/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_flags_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmentat <gmentat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:46:05 by gmentat           #+#    #+#             */
/*   Updated: 2019/12/30 14:01:35 by gmentat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_arg		*check_length_p(t_arg *args, t_f_arg *struct_flugs)
{
	args->len = ft_strlen(args->str_result);
	if (struct_flugs->point != NULL && struct_flugs->i_point == 0 &&
		(*(args->str_result) == '0' && args->u.val == 0))
	{
		args->len = 2;
	}
	return (args);
}

t_arg		*helper_use_flags_p(t_f_arg *s, t_arg *args, int j)
{
	s->width = ft_strnew(s->i_width - (int)ft_strlen(args->str_result));
	while (j < (s->i_width - (int)ft_strlen(args->str_result)))
	{
		s->width[j] = ' ';
		j++;
	}
	if (s->minus == NULL)
		args->str_result = ft_fundel(args->str_result, s->width, 1, 2);
	else
		args->str_result = ft_fundel(args->str_result, s->width, 0, 2);
	return (args);
}

char		*struct_flugs_length_p(t_arg *args, va_list ap)
{
	args->u.val_ul = va_arg(ap, unsigned long);
	args->str_result = ft_itoa_base(args->u.val_ul, 16);
	return (args->str_result);
}

t_f_arg		*struct_flugs_p(t_f_arg *struct_flugs)
{
	struct_flugs->grill = NULL;
	struct_flugs->zero = NULL;
	struct_flugs->plus = NULL;
	struct_flugs->spase = NULL;
	struct_flugs->grill = NULL;
	return (struct_flugs);
}

t_arg		*use_flags_p(t_f_arg *s, t_arg *args, va_list ap, int j)
{
	s = struct_flugs_p(s);
	args->str_result = struct_flugs_length_p(args, ap);
	if (s->i_point > (int)ft_strlen(args->str_result))
	{
		s->point = NULL;
		s->point = ft_strnew(s->i_point - (int)ft_strlen(args->str_result));
		while (j < (s->i_point - (int)ft_strlen(args->str_result)))
		{
			s->point[j] = '0';
			j++;
		}
		args->str_result = ft_fundel(args->str_result, s->point, 1, 2);
	}
	if (s->point != NULL && args->u.val == 0 && s->i_point != 0)
		args->str_result = ft_fundel(args->str_result, "0x", 2, 1);
	else if (s->point != NULL && args->u.val == 0 && s->i_point == 0)
		args->str_result = ft_fundel(args->str_result, "x", 2, 0);
	else
		args->str_result = ft_fundel(args->str_result, "0x", 2, 1);
	if (s->i_width > (int)ft_strlen(args->str_result))
		args = helper_use_flags_p(s, args, 0);
	args = check_length_p(args, s);
	return (args);
}
