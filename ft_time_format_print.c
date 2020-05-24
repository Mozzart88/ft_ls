/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_format_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 20:40:20 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/24 20:46:43 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_print_time_ru(t_datetime *dt, long long dif_time)
{
	char		*f;

	f = "%2s %6s %02s:%02s ";
	if (dif_time < (31536000L / 2) && dif_time >= 0)
		ft_printf(f, (dt)->mday, (dt)->monstr, (dt)->hour, (dt)->min);
	else
	{
		ft_printf("%2s %6s ", (dt)->mday, (dt)->monstr);
		ft_printf("%* s ", ft_strlen(dt->year) + 1, dt->year);
	}
}

void		ft_print_time_us(t_datetime *dt, long long dif_time)
{
	char *f;

	f = "%3s %2s %02s:%02s ";
	if (dif_time < (31536000L / 2) && dif_time > (31536000L / 2 * -1))
		ft_printf(f, (dt)->monstr, (dt)->mday, (dt)->hour, (dt)->min);
	else
	{
		ft_printf("%3s %2s ", (dt)->monstr, (dt)->mday);
		ft_printf("%* s ", ft_strlen(dt->year) + 1, dt->year);
	}
}
