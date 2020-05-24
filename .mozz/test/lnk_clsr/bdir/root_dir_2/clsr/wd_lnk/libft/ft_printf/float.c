/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 20:15:52 by tvanessa          #+#    #+#             */
/*   Updated: 2020/01/06 18:51:14 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void					ft_swap(t_v **a, t_v **b)
{
	t_v *s;

	s = *b;
	*b = *a;
	*a = s;
}

char					*ft_exception_handler(t_ull arr[2])
{
	if ((arr[1] & 0x7FFF) != 0x7FFF)
		return (NULL);
	if (!arr[0] || (!(arr[0] << 1) && (arr[0] >> 63)))
		return (arr[1] & 0x8000 ? "-inf" : "inf");
	return ("nan");
}

static t_v				*ft_make_man_bias(void)
{
	t_v				*v;
	t_us			vals[12];

	vals[0] = 8125;
	vals[1] = 4257;
	vals[2] = 1711;
	vals[3] = 6994;
	vals[4] = 8008;
	vals[5] = 7452;
	vals[6] = 3400;
	vals[7] = 5044;
	vals[8] = 2485;
	vals[9] = 217;
	vals[10] = 842;
	vals[11] = 1;
	v = ft_create_vector(12);
	v->nbr_set(v, vals, 12);
	v->point = 63;
	return (v);
}

char					*get_float(long double val, t_us p)
{
	t_ldbl_to_ull	u;
	t_v				*exp;
	t_v				*frac;
	char			*res;

	u.ld = val;
	if (ft_exception_handler(u.llu))
		return (ft_exception_handler(u.llu));
	frac = ft_make_long_vector(u.llu[0] & 0x7FFFFFFFFFFFFFFF);
	exp = ft_make_man_bias();
	ft_mult_vects(frac, exp, 0);
	exp->destroy(exp);
	frac->add(frac, frac->point ? (exp = ft_pow_vec(10, frac->point)) :\
	(exp = ft_make_long_vector(1)));
	exp->destroy(exp);
	exp = ft_pow_vec(2, (int)((u.llu[1]) & 0x7fff) - 16383);
	ft_mult_vects(exp, frac, 0);
	frac->destroy(frac);
	if (u.llu[1] & 0x8000)
		exp->neg = 1;
	res = exp->to_str(exp, p);
	exp->destroy(exp);
	return (res);
}
