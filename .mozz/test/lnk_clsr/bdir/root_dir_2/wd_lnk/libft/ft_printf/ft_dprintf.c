/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmentat <gmentat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 20:35:00 by gmentat           #+#    #+#             */
/*   Updated: 2019/12/25 20:35:32 by gmentat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_dprintf(int fd, const char *restrict format, ...)
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
		i = parsing_str_format_fd(arg, ap, format, fd);
		va_end(ap);
	}
	free(arg);
	return (i);
}
