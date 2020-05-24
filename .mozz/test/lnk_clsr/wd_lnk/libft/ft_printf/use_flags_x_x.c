/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_flags_x_x.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:15:25 by gmentat           #+#    #+#             */
/*   Updated: 2020/01/07 15:23:00 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_arg	*helper_use_flags_x_x(t_arg *args)
{
	if (args->type == 'X' && args->u.val_ui != 0)
	{
		ft_strtoupper(args->str_result);
		args->str_result = ft_fundel(args->str_result, "0X", 2, 1);
	}
	if (args->type == 'x' && args->u.val_ui != 0)
		args->str_result = ft_fundel(args->str_result, "0x", 2, 1);
	return (args);
}

t_arg	*check_length_x_x(t_arg *args, t_f_arg *struct_flugs)
{
	args->len = ft_strlen(args->str_result);
	if (struct_flugs->point != NULL && struct_flugs->i_point == 0 &&
		(*(args->str_result) == '0' && args->u.val == 0))
	{
		args->len = args->len + 1;
	}
	return (args);
}

t_f_arg	*struct_flugs_x_x(t_f_arg *struct_flugs)
{
	struct_flugs->plus = NULL;
	struct_flugs->spase = NULL;
	if (struct_flugs->zero != NULL && struct_flugs->point != NULL)
		struct_flugs->zero = NULL;
	if (struct_flugs->zero != NULL && struct_flugs->minus != NULL)
		struct_flugs->zero = NULL;
	return (struct_flugs);
}

t_arg	*use_flags_x_x(t_f_arg *struct_flugs, t_arg *args, va_list ap)
{
	struct_flugs = struct_flugs_x_x(struct_flugs);
	args->str_result = struct_flugs_length_x_x(struct_flugs, args, ap);
	if (struct_flugs->i_point > (int)ft_strlen(args->str_result))
		use_mod_point(struct_flugs, args);
	if ((struct_flugs->grill != NULL && args->u.val_ui != 0 &&
		(struct_flugs->i_width <= (int)ft_strlen(args->str_result) ||
		struct_flugs->zero == NULL)))
		args = helper_use_flags_x_x(args);
	if ((struct_flugs->less_zero != NULL && struct_flugs->zero == NULL) ||
		(struct_flugs->less_zero != NULL && (struct_flugs->zero != NULL &&
		struct_flugs->i_width < (int)ft_strlen(args->str_result))))
		args->str_result = ft_fundel(args->str_result, "-", 2, 1);
	else if ((struct_flugs->zero == NULL || struct_flugs->point != NULL) &&
		struct_flugs->plus != NULL)
		args->str_result = ft_fundel(args->str_result, "+", 2, 1);
	else if ((struct_flugs->zero == NULL || struct_flugs->point != NULL) &&
		struct_flugs->spase != NULL)
		args->str_result = ft_fundel(args->str_result, " ", 2, 1);
	if (struct_flugs->i_width > (int)ft_strlen(args->str_result))
		args = use_mod_width(struct_flugs, args, 0);
	if (args->type == 'X')
		ft_strtoupper(args->str_result);
	args = check_length_x_x(args, struct_flugs);
	return (args);
}
