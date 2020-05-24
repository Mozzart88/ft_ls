/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 12:49:24 by tvanessa          #+#    #+#             */
/*   Updated: 2020/01/06 19:55:19 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				ft_vector_addition_by_index(t_v *v, t_us n, t_us i)
{
	t_ull	tr;

	tr = (t_ull)n;
	while ((tr += v->nbr[i]))
	{
		v->nbr[i] = tr % 10000;
		tr /= 10000;
		i++;
	}
	if (i > v->size)
		v->size = i;
}

void				ft_vector_addition_by_index_r(t_v *v, t_us n, t_us i)
{
	t_ull	tr;

	tr = (t_ull)n;
	while (tr && (tr += v->r_val[i]))
	{
		v->r_val[i] = tr % 10000;
		tr /= 10000;
		i++;
		if (i >= v->size && tr)
			v->resize_r(v, i + 1);
	}
	if (i > v->size)
		v->size = i;
}

void				ft_vector_addition(t_v *v, t_v *a)
{
	t_us	tr;
	t_us	i;
	t_us	x[v->size + a->size];

	tr = 0;
	i = 0;
	ft_clear_arr(x, v->size + a->size);
	while (i < (v->size < a->size ? a->size : v->size) || tr)
	{
		if (a->nbr[i] && i < a->size)
			tr += a->nbr[i];
		if (v->nbr[i] && i < v->size)
			tr += v->nbr[i];
		x[i] += tr % 10000;
		tr /= 10000;
		++i;
	}
	v->nbr_set(v, x, i);
}

t_v					*ft_mult_vects(t_v *a, t_v *b, t_us swaped)
{
	short	i[3];
	t_us	x[a->size + b->size];
	t_v		*res;

	if (a->size < b->size)
		return (ft_mult_vects(b, a, 1));
	res = swaped ? b : a;
	res->point = a->point + b->point;
	if (b->size == 1 && b->nbr[0] == 1)
		return (swaped ? b->nbr_set(b, a->nbr, a->size) : a);
	ft_clear_arr(x, a->size + b->size);
	i[2] = 0;
	while (a->size + b->size > i[2])
	{
		i[0] = i[2];
		while (i[0] >= 0 && (i[1] = i[2] - i[0]) >= 0)
		{
			if ((i[0] < a->size && i[1] < (a == b ? a->size : b->size)))
				ft_arr_add_to(x, (t_ull)(a->nbr[i[0]] * b->nbr[i[1]]),\
				i[0] + i[1]);
			--i[0];
		}
		++i[2];
	}
	return (res->nbr_set(res, x, i[2]));
}

t_v					*ft_pow_vec(t_ull x, int p)
{
	t_v		*res;
	t_v		*ix;

	if (p < 0)
	{
		p *= -1;
		res = ft_pow_vec(5, p);
		res->point = p;
		return (res);
	}
	res = ft_make_long_vector(1);
	ix = ft_make_long_vector(x);
	while (p)
	{
		if (p & 1)
		{
			ft_mult_vects(res, ix, 0);
			if (!(--p))
				break ;
		}
		ft_mult_vects(ix, ix, 0);
		p >>= 1;
	}
	ix->destroy(ix);
	return (res);
}
