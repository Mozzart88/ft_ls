/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_flugs_length_u.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmentat <gmentat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 19:29:31 by gmentat           #+#    #+#             */
/*   Updated: 2019/12/30 14:01:35 by gmentat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	s_f_l_h_u(t_f_arg *struct_flugs, t_arg *args, va_list ap)
{
	args->u.val_ui = va_arg(ap, unsigned int);
	if (struct_flugs->fh != NULL)
		args->str_result = ft_itoa(args->u.val_uh);
	else if (struct_flugs->fhh != NULL)
		args->str_result = ft_itoa(args->u.val_uc);
	else if (args->u.val > 0)
		args->str_result = ft_itoa_long_un(args->u.val_ui);
	else
		args->str_result = ft_itoa(args->u.val_ui);
}

char	*struct_flugs_length_u(t_f_arg *struct_flugs, t_arg *args, va_list ap)
{
	if (args->type == 'U')
	{
		args->u.val_ul = va_arg(ap, long int);
		args->str_result = ft_itoa_long_un(args->u.val_ul);
	}
	else if (struct_flugs->fl != NULL || struct_flugs->z != NULL)
	{
		args->u.val_ul = va_arg(ap, unsigned long);
		args->str_result = ft_itoa_long_un(args->u.val_ul);
	}
	else if (struct_flugs->t != NULL || struct_flugs->j != NULL)
	{
		args->u.val_ll = va_arg(ap, long long int);
		args->str_result = ft_itoa_long_un(args->u.val_ll);
	}
	else if (struct_flugs->fll != NULL)
	{
		args->u.val_ull = va_arg(ap, unsigned long long);
		args->str_result = ft_itoa_long_un(args->u.val_ull);
	}
	else
		s_f_l_h_u(struct_flugs, args, ap);
	return (args->str_result);
}
