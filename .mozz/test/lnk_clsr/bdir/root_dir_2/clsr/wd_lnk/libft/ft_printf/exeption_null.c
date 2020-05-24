/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeption_null.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmentat <gmentat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 18:22:04 by gmentat           #+#    #+#             */
/*   Updated: 2019/12/30 13:55:03 by gmentat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_arg		*helper_exeption_null(t_arg *args, t_f_arg *s_f, int i, int j)
{
	if (s_f->minus != NULL)
	{
		args->str_result[j] = '\0';
		j++;
		while (j < i)
		{
			args->str_result[j] = ' ';
			j++;
		}
		args->len = j;
	}
	else if (s_f->minus == NULL)
	{
		while (j < i)
		{
			args->str_result[j] = ' ';
			j++;
		}
		args->str_result[j - 1] = '\0';
		args->len = j;
	}
	ft_strdel(&s_f->width);
	return (args);
}

t_arg		*exeption_null(t_arg *args, t_f_arg *s_f, int i, int j)
{
	i = ft_strlen(s_f->width);
	ft_strdel(&args->str_result);
	args->str_result = ft_strnew(i);
	if (s_f->width != NULL && s_f->i_width > 1)
	{
		args = helper_exeption_null(args, s_f, i, j);
	}
	else
		args->len = 1;
	return (args);
}
