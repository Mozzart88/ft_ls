/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmentat <gmentat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:51:18 by tvanessa          #+#    #+#             */
/*   Updated: 2020/01/03 18:30:58 by gmentat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *restrict format, ...)
{
	t_arg		*arg;
	va_list		ap;
	int			i;

	i = 0;
	arg = ft_newarg('q');
	ft_bzero(arg->buff, SIZE);
	if (format)
	{
		va_start(ap, format);
		i = parsing_str_format(arg, ap, format);
		va_end(ap);
	}
	free(arg);
	return (i);
}
