/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 12:57:57 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/17 16:10:57 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_ull				ft_pow(t_ull x, int p)
{
	t_ull	res;

	res = 1;
	if (p < 0)
		p = 0;
	while (p)
	{
		if (p & 1)
		{
			res *= x;
			--p;
		}
		x *= x;
		p >>= 1;
	}
	return (res);
}

t_us				ft_count_digits(t_ull n)
{
	t_us	p;
	t_us	r;

	r = 0;
	p = 1;
	while (n != 0)
	{
		++r;
		n /= 10;
	}
	return (r);
}
