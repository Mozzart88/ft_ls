/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_mod_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 20:47:19 by gmentat           #+#    #+#             */
/*   Updated: 2020/01/07 14:33:17 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		finish_mod_fd(t_arg *args)
{
	int i;

	i = 0;
	while (i < args->len)
	{
		if (args->index_buff == SIZE)
		{
			if ((args->c_w = write(args->fd, args->buff, SIZE)) < 0)
				args->value = (-1);
			args->index_buff = 0;
			ft_bzero(args->buff, SIZE);
			args->value = args->value + SIZE;
		}
		args->buff[args->index_buff] = args->str_result[i];
		++i;
		++args->index_buff;
	}
	ft_strdel(&args->str_result);
}
