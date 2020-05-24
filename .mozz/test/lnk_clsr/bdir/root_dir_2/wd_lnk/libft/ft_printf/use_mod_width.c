/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_mod_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmentat <gmentat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:13:29 by gmentat           #+#    #+#             */
/*   Updated: 2019/12/30 14:24:21 by gmentat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_arg	*helper_use_mod_width(t_f_arg *struct_flugs, t_arg *args, int j)
{
	while (j < (struct_flugs->i_width - (int)ft_strlen(args->str_result)))
	{
		struct_flugs->width[j] = '0';
		j++;
	}
	args->str_result = ft_fundel(args->str_result, struct_flugs->width, 1, 3);
	if (args->type == 'o' && struct_flugs->grill != NULL &&
		struct_flugs->zero != NULL && args->u.val_ui != 0)
		args->str_result = ft_memmove(args->str_result, "0", 1);
	if ((args->type == 'x' || args->type == 'X') &&
		struct_flugs->grill != NULL &&
		struct_flugs->zero != NULL && args->u.val_ui != 0)
	{
		if (args->type == 'X')
			args->str_result = ft_memmove(args->str_result, "0X", 2);
		if (args->type == 'x')
			args->str_result = ft_memmove(args->str_result, "0x", 2);
	}
	if (struct_flugs->less_zero != NULL)
		args->str_result = ft_memmove(args->str_result, "-", 1);
	else if (struct_flugs->plus != NULL)
		args->str_result = ft_memmove(args->str_result, "+", 1);
	else if (struct_flugs->spase != NULL)
		args->str_result = ft_memmove(args->str_result, " ", 1);
	return (args);
}

t_arg	*use_mod_width(t_f_arg *st_f, t_arg *args, int j)
{
	st_f->width = ft_strnew(st_f->i_width - (int)ft_strlen(args->str_result));
	if (st_f->zero == NULL || (st_f->zero != NULL &&
		st_f->point != NULL && args->type != 'f'))
	{
		while (j < (st_f->i_width - (int)ft_strlen(args->str_result)))
		{
			st_f->width[j] = ' ';
			j++;
		}
		if (st_f->minus == NULL)
			args->str_result = ft_fundel(args->str_result, st_f->width, 1, 3);
		else
			args->str_result = ft_fundel(args->str_result, st_f->width, 0, 3);
	}
	else if ((st_f->zero != NULL && st_f->point == NULL) ||
		(st_f->zero != NULL && args->type == 'f'))
		args = helper_use_mod_width(st_f, args, 0);
	return (args);
}
