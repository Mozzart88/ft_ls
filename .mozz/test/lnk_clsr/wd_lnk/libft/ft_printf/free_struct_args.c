/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:56:02 by gmentat           #+#    #+#             */
/*   Updated: 2020/01/07 14:32:22 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		free_struct_args(t_arg *args)
{
	args->c_w = 0;
	args->str_result = NULL;
	args->s_str = NULL;
	args->flags = NULL;
	args->type = 0;
	args->len = 0;
	args->u.val_ui = 0;
	args->u.val = 0;
	args->u.val_c = 0;
	args->u.val_uc = 0;
	args->u.val_h = 0;
	args->u.val_uh = 0;
	args->u.val_l = 0;
	args->u.val_ul = 0;
	args->u.val_ll = 0;
	args->u.val_ull = 0;
	args->u.val_f = 0;
	args->u.val_ld = 0;
}
