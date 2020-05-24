/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_flags_o.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:15:25 by gmentat           #+#    #+#             */
/*   Updated: 2020/01/07 15:23:15 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_arg		*check_length_o(t_arg *args)
{
	args->len = ft_strlen(args->str_result);
	return (args);
}

t_f_arg		*struct_flugs_o(t_f_arg *struct_flugs)
{
	struct_flugs->plus = NULL;
	struct_flugs->spase = NULL;
	if (struct_flugs->zero != NULL && struct_flugs->point != NULL)
		struct_flugs->zero = NULL;
	if (struct_flugs->zero != NULL && struct_flugs->minus != NULL)
		struct_flugs->zero = NULL;
	return (struct_flugs);
}

t_arg		*use_flags_o(t_f_arg *struct_flugs, t_arg *args, va_list ap)
{
	struct_flugs = struct_flugs_o(struct_flugs);
	args->str_result = struct_flugs_length_o(struct_flugs, args, ap);
	if (struct_flugs->grill != NULL &&
		struct_flugs->i_point <= (int)ft_strlen(args->str_result) &&
		args->u.val_ui != 0)
		args->str_result = ft_fundel(args->str_result, "0", 2, 1);
	if (struct_flugs->i_point > (int)ft_strlen(args->str_result))
		use_mod_point(struct_flugs, args);
	if (struct_flugs->grill != NULL && args->u.val_ui == 0 &&
		struct_flugs->i_point == 0 && struct_flugs->point != NULL)
		args->str_result = ft_fundel(args->str_result, "0", 2, 1);
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
	args = check_length_o(args);
	return (args);
}
