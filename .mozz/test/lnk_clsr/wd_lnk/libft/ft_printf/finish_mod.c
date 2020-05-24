/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:51:21 by gmentat           #+#    #+#             */
/*   Updated: 2020/01/07 14:31:51 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		finish_mod(t_arg *args)
{
	int i;

	i = 0;
	while (i < args->len)
	{
		if (args->index_buff == SIZE)
		{
			if ((args->c_w = write(1, args->buff, SIZE)) < 0)
				args->value = (-1);
			args->index_buff = 0;
			ft_bzero(args->buff, SIZE);
			args->value += SIZE;
		}
		args->buff[args->index_buff] = args->str_result[i];
		++i;
		++args->index_buff;
	}
	ft_strdel(&args->str_result);
}
