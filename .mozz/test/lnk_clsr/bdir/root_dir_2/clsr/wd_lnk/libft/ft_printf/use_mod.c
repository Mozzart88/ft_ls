/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_mod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 05:35:41 by gmentat           #+#    #+#             */
/*   Updated: 2020/01/07 15:20:30 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		use_mod_helper_two(t_f_arg *struct_flugs, t_arg *args, va_list ap)
{
	if (args->type == 'd' || args->type == 'i')
		use_flags_d_i(struct_flugs, args, ap);
	else if (args->type == 'x' || args->type == 'X')
		use_flags_x_x(struct_flugs, args, ap);
	else if (args->type == 'o')
		use_flags_o(struct_flugs, args, ap);
	else if (args->type == 'u' || args->type == 'U')
		use_flags_u(struct_flugs, args, ap);
	else if (args->type == 'c')
		use_flags_c(struct_flugs, args, ap);
	else if (args->type == 's')
		use_flags_s(struct_flugs, args, ap);
	else if (args->type == 'p')
		use_flags_p(struct_flugs, args, ap, 0);
	else if (args->type == 'f')
		use_flags_f(struct_flugs, args, ap);
	else if (args->type == '%')
		use_flags_proc(struct_flugs, args);
}

void		use_mod_helper(t_f_arg *struct_flugs, t_arg *args)
{
	args->index_f = -1;
	free_struct_args(args);
	free_struct_flugs(struct_flugs);
	args->value = 0;
}

void		use_mod(t_f_arg *struct_flugs, t_arg *args, va_list ap)
{
	if (struct_flugs->exeptions < 0 || args->value < 0)
		use_mod_helper(struct_flugs, args);
	else
		use_mod_helper_two(struct_flugs, args, ap);
	if (args->fd > 0)
		finish_mod_fd(args);
	else
		finish_mod(args);
	free_struct_args(args);
	free_struct_flugs(struct_flugs);
}
