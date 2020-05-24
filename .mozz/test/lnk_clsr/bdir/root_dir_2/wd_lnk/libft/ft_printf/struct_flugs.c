/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_flugs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 20:26:16 by gmentat           #+#    #+#             */
/*   Updated: 2020/01/06 23:07:08 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_f_arg		*st_flags(t_arg *args, t_f_arg *flags_struct, va_list ap)
{
	char	*copy_flags;

	copy_flags = args->flags;
	if (!args->flags)
	{
		copy_flags = NULL;
		return (flags_struct);
	}
	if (args->value < 0)
	{
		args->index_f = -1;
		return (flags_struct);
	}
	flags_struct->yes = ft_strnew(1);
	flags_struct->yes[0] = 'y';
	parse_flags_width(flags_struct, copy_flags, args->type, ap);
	parse_flags_point(flags_struct, copy_flags, args->type, ap);
	parse_flags_length(flags_struct, copy_flags);
	parse_flags_basic(flags_struct, copy_flags, 0);
	copy_flags = NULL;
	ft_strdel(&args->flags);
	return (flags_struct);
}
