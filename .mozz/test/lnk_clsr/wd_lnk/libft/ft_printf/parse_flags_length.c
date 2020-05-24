/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags_length.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:39:28 by gmentat           #+#    #+#             */
/*   Updated: 2020/01/06 23:15:39 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		parse_flags_length(t_f_arg *length_flags, char *flags)
{
	if (ft_strstr(flags, "hh"))
		length_flags->fhh = length_flags->yes;
	else if (ft_strchr(flags, 'h'))
		length_flags->fh = length_flags->yes;
	if (ft_strstr(flags, "ll"))
		length_flags->fll = length_flags->yes;
	else if (ft_strchr(flags, 'l'))
		length_flags->fl = length_flags->yes;
	else if (ft_strchr(flags, 'L'))
		length_flags->fll = length_flags->yes;
	if (ft_strchr(flags, 'j'))
		length_flags->j = length_flags->yes;
	if (ft_strchr(flags, 'z'))
		length_flags->z = length_flags->yes;
	if (ft_strchr(flags, 't'))
		length_flags->t = length_flags->yes;
}
