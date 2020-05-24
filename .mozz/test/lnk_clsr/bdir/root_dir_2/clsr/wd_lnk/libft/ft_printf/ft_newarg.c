/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newarg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmentat <gmentat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 16:43:48 by gmentat           #+#    #+#             */
/*   Updated: 2020/01/03 22:37:53 by gmentat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_arg	*ft_newarg_helper(t_arg *res, char type)
{
	res->c_w = 0;
	res->str_result = NULL;
	res->s_str = NULL;
	res->flags = NULL;
	res->type = type;
	res->index_buff = 0;
	res->index_f = 0;
	res->value = 0;
	res->len = 0;
	res->dup = NULL;
	res->fd = 0;
	res->u.val_ui = 0;
	res->u.val = 0;
	res->u.val_c = 0;
	res->u.val_uc = 0;
	res->u.val_h = 0;
	res->u.val_uh = 0;
	res->u.val_l = 0;
	res->u.val_ul = 0;
	res->u.val_ll = 0;
	res->u.val_ull = 0;
	res->u.val_f = 0;
	res->u.val_ld = 0;
	return (res);
}

t_arg	*ft_newarg(char type)
{
	t_arg			*res;

	if (!(res = (t_arg*)malloc(sizeof(t_arg))))
		return (NULL);
	return (ft_newarg_helper(res, type));
}
