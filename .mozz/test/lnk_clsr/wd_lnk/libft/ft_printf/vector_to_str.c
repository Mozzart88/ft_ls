/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 12:53:53 by tvanessa          #+#    #+#             */
/*   Updated: 2020/01/06 19:55:19 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_us				ft_setstr_helper(t_v *v, t_us x[3], t_us y[2])
{
	if (x[0] < 0 ||\
	(y[0] == v->size - 1 &&\
	(v->r_val[y[0]] / y[1]) == 0 &&\
	(x[1] - x[0] < 0)))
		return (1);
	return (0);
}

char				ft_setstr_get_digit(t_v *v, t_us y[2])
{
	return (y[0] < v->size ? (v->r_val[y[0]] / y[1] % 10) + '0' : '0');
}

void				ft_setstr(char *str, t_v *v, t_us x[3])
{
	t_us	y[2];

	y[0] = 0;
	while (y[0] < v->size || !str[0])
	{
		y[1] = 1;
		while (y[1] <= 1000)
		{
			--x[0];
			if ((x[1] - v->point != x[2] && (x[1] - x[0]) == v->point + 1))
			{
				str[x[0]] = '.';
				--x[0];
				--x[2];
			}
			if (x[0] < x[2])
			{
				if (ft_setstr_helper(v, x, y))
					break ;
				str[x[0]] = ft_setstr_get_digit(v, y);
			}
			y[1] *= 10;
		}
		++y[0];
	}
}

char				*ft_vector_to_str(t_v *v, t_us pr)
{
	char		*str;
	t_us		x[3];

	if (!v->size)
		return ("0");
	if (!(ft_vector_round(v, pr)))
		return (NULL);
	x[0] = (pr ? v->dcount(v) + 1 : v->dcount(v)) + v->neg;
	x[1] = x[0];
	x[2] = x[0] - v->point + pr;
	if (!(str = ft_strnew(x[2] + v->neg)))
		return (NULL);
	if (x[2] > x[0])
	{
		ft_memset((str + x[0]), '0', x[2] - x[0]);
		if (v->point == 0)
			str[--x[0]] = '.';
	}
	ft_setstr(str, v, x);
	if (!ft_isdigit(str[0]))
		str[0] = '0';
	if (v->neg)
		str[0] = '-';
	return (str);
}
