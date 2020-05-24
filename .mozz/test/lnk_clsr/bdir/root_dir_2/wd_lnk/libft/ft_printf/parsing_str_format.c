/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_str_format.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 16:55:20 by gmentat           #+#    #+#             */
/*   Updated: 2020/01/06 21:51:17 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_arg	*mod_in_helper(const char *format, t_arg *args, int i)
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

t_arg	*write_char_no_mod(t_arg *args, char c)
{
	if (args->index_buff == SIZE)
	{
		if ((args->c_w = write(1, args->buff, SIZE)) < 0)
			args->value = (-1);
		args->index_buff = 0;
		ft_bzero(args->buff, SIZE);
		args->value = args->value + SIZE;
	}
	args->buff[args->index_buff] = c;
	++args->index_buff;
	++args->index_f;
	return (args);
}

t_arg	*mod_in(const char *format, t_arg *args)
{
	int		i;
	int		p;

	i = 0;
	p = 1;
	++format;
	while (format[i])
	{
		if (ft_strchr("cspdiouxXfy%U", format[i]))
		{
			args = mod_in_helper(format, args, i);
			break ;
		}
		if (ft_strchr("# -+*.0123456789hLljzt%", format[i]))
			++p;
		else
			break ;
		++i;
	}
	if (args->flags)
		args->index_f = i + 2;
	else
		args->index_f = p;
	return (args);
}

int		parsing_str_format(t_arg *a, va_list ap, const char *f)
{
	t_f_arg		*fl_st;

	fl_st = ft_newarg_flags();
	while (*f)
	{
		if (*f == 37)
		{
			use_mod(st_flags((mod_in(f, a)), fl_st, ap), a, ap);
			if (a->index_f < 0)
				break ;
			f = f + a->index_f;
			a->index_f = 0;
		}
		else
		{
			a = write_char_no_mod(a, *f);
			f++;
		}
	}
	if (*f == 0 && ((a->c_w = write(1, a->buff, a->index_buff)) < 0))
		return (a->value = (-1));
	a->value = a->value + a->index_buff;
	free(fl_st);
	return (a->value);
}
