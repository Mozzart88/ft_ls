/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_flags_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmentat <gmentat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:44:13 by gmentat           #+#    #+#             */
/*   Updated: 2019/12/30 14:00:58 by gmentat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_arg		*check_length_c(t_arg *args)
{
	if ((ft_strlen(args->str_result)) > 1 && args->u.val != 0)
	{
		args->len = ft_strlen(args->str_result);
		return (args);
	}
	return (args);
}

t_arg		*helper_use_flags_c(t_f_arg *st_f, t_arg *args, int j)
{
	st_f->width = ft_strnew(st_f->i_width - (int)ft_strlen(args->str_result));
	while (j < (st_f->i_width - (int)ft_strlen(args->str_result)))
	{
		st_f->width[j] = ' ';
		j++;
	}
	if (st_f->zero != NULL)
		st_f->width = ft_memset(st_f->width, '0', j);
	if (st_f->minus == NULL)
		args->str_result = ft_fundel(args->str_result, st_f->width, 1, 2);
	else
		args->str_result = ft_fundel(args->str_result, st_f->width, 0, 2);
	args = check_length_c(args);
	return (args);
}

char		*struct_flugs_length_c(t_arg *args, va_list ap)
{
	args->u.val_uc = va_arg(ap, int);
	args->str_result = ft_strnew(1);
	args->str_result[0] = args->u.val_uc;
	return (args->str_result);
}

t_f_arg		*struct_flugs_c(t_f_arg *struct_flugs)
{
	struct_flugs->grill = NULL;
	struct_flugs->i_point = 0;
	struct_flugs->plus = NULL;
	struct_flugs->spase = NULL;
	struct_flugs->grill = NULL;
	return (struct_flugs);
}

t_arg		*use_flags_c(t_f_arg *s_f, t_arg *args, va_list ap)
{
	int j;

	j = 0;
	s_f = struct_flugs_c(s_f);
	args->str_result = struct_flugs_length_c(args, ap);
	if (*(args->str_result) == '\0')
	{
		s_f->width = ft_strnew(s_f->i_width - (int)ft_strlen(args->str_result));
		while (j < (s_f->i_width - (int)ft_strlen(args->str_result)))
		{
			s_f->width[j] = ' ';
			j++;
		}
		args = exeption_null(args, s_f, 0, 0);
	}
	else if (s_f->i_width > (int)ft_strlen(args->str_result))
		args = helper_use_flags_c(s_f, args, 0);
	else
		args->len = 1;
	return (args);
}
