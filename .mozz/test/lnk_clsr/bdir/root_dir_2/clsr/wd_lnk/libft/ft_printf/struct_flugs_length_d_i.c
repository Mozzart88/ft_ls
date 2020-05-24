/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_flugs_length_d_i.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmentat <gmentat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 18:48:43 by gmentat           #+#    #+#             */
/*   Updated: 2019/12/30 14:01:07 by gmentat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	s_f_l_h_d_i(t_f_arg *s_f, t_arg *args, va_list ap)
{
	if (s_f->fl != NULL)
	{
		args->u.val = va_arg(ap, long int);
		args->str_result = ft_itoa_long(args->u.val_l);
	}
	else if (s_f->z != NULL)
	{
		args->u.val_ul = va_arg(ap, unsigned long int);
		args->str_result = ft_itoa_long(args->u.val_ul);
	}
	else if (s_f->fll != NULL || s_f->j != NULL || s_f->t != NULL)
	{
		args->u.val = va_arg(ap, long long int);
		args->str_result = ft_itoa_long(args->u.val_ll);
	}
	else
	{
		args->u.val = va_arg(ap, int);
		if (s_f->fh != NULL)
			args->str_result = ft_itoa(args->u.val_h);
		else if (s_f->fhh != NULL)
			args->str_result = ft_itoa(args->u.val_c);
		else
			args->str_result = ft_itoa(args->u.val);
	}
}

char	*struct_flugs_length_d_i(t_f_arg *struct_flugs, t_arg *args, va_list ap)
{
	s_f_l_h_d_i(struct_flugs, args, ap);
	if (struct_flugs->point != NULL && struct_flugs->i_point == 0 &&
		(*(args->str_result) == '0' && args->u.val == 0))
		args->str_result = ft_strnew(0);
	return (args->str_result);
}
