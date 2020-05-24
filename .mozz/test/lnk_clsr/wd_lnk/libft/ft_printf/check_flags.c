/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:30:53 by gmentat           #+#    #+#             */
/*   Updated: 2020/01/06 21:41:48 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		check_flags(t_arg *a)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (a->flags[j])
	{
		if (a->type == 37)
			return (0);
		if (ft_strchr("# -+*.0123456789hLlcspdiouxXfjztU%", a->flags[j]))
			++j;
		else
			return (-2);
	}
	return (0);
}
