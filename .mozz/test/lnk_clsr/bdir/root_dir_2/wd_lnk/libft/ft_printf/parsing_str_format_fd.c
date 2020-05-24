/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_str_format_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmentat <gmentat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 20:15:34 by gmentat           #+#    #+#             */
/*   Updated: 2019/12/30 14:01:15 by gmentat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_arg	*mod_in_fd_helper(const char *format, t_arg *args, int i)
{
	args->type = format[i];
	args->flags = ft_strnew(i + 1);
	args->flags = ft_strncpy(args->flags, format, i + 1);
	if ((check_flags(args)) < 0)
	{
		args->value = -1;
		ft_strdel(&args->flags);
	}
	return (args);
}

t_arg	*write_char_no_mod_fd(t_arg *args, char c)
{
	if (args->index_buff == SIZE)
	{
		if ((args->c_w = write(args->fd, args->buff, SIZE)) < 0)
			args->value = (-1);
		args->index_buff = 0;
		ft_bzero(args->buff, SIZE);
		args->value = args->value + SIZE;
	}
	args->buff[args->index_buff] = c;
	args->index_buff++;
	args->index_f++;
	return (args);
}

t_arg	*mod_in_fd(const char *format, t_arg *args)
{
	int		i;
	int		p;

	i = 0;
	p = 1;
	format++;
	while (format[i] != '\0')
	{
		if (ft_strchr("cspdiouxXfy%U", format[i]) != NULL)
		{
			args = mod_in_fd_helper(format, args, i);
			break ;
		}
		if (ft_strchr("# -+*.0123456789hLljzt%", format[i]) != NULL)
			p++;
		else
			break ;
		i++;
	}
	if (args->flags)
		args->index_f = i + 2;
	if (!args->flags)
		args->index_f = p;
	return (args);
}

int		parsing_str_format_fd(t_arg *a, va_list ap, const char *f, int fd)
{
	t_f_arg		*fl_st;

	fl_st = ft_newarg_flags();
	a->fd = fd;
	while (*f)
	{
		if (*f == '%')
		{
			use_mod(st_flags((mod_in_fd(f, a)), fl_st, ap), a, ap);
			if (a->index_f < 0)
				break ;
			f = f + a->index_f;
			a->index_f = 0;
		}
		else
		{
			a = write_char_no_mod_fd(a, *f);
			f++;
		}
	}
	if (*f == '\0' && ((a->c_w = write(a->fd, a->buff, a->index_buff)) < 0))
		return (a->value = (-1));
	a->value = a->value + a->index_buff;
	free(fl_st);
	return (a->value);
}
