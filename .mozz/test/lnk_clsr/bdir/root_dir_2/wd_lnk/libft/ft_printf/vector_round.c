/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_round.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 12:54:57 by tvanessa          #+#    #+#             */
/*   Updated: 2020/01/06 19:55:19 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_v					*ft_round_helper(t_v *v, t_us pr, t_us dcc, t_us i)
{
	t_us	p;
	t_us	n;
	t_us	tv;

	while (i < v->size && pr <= dcc)
	{
		p = 1;
		n = 0;
		while (n < 4 && pr <= dcc)
		{
			tv = v->nbr[i] / p % 10;
			if (pr == dcc && tv >= 5)
				v->add_to_r(v, p * 10, i);
			--dcc;
			p *= 10;
			++n;
		}
		++i;
	}
	return (v);
}

t_v					*ft_vector_round(t_v *v, t_us pr)
{
	t_us		i;
	t_us		to_str;
	t_us		dc;

	if (!(v->r_val = (t_us*)malloc(sizeof(t_us) * v->size)))
		return (NULL);
	ft_clear_arr(v->r_val, v->size);
	ft_arrcpy(v->r_val, v->nbr, v->size);
	dc = v->dcount(v);
	if (pr > dc || !v->point)
		return (v);
	i = 0;
	to_str = dc - v->point + pr;
	i = 0;
	dc = (v->size - 1) * 4;
	dc += ft_count_digits(v->nbr[v->size - 1]);
	if (dc <= v->point)
		pr = pr - (v->point - dc) + 1;
	else
		pr = to_str + 1;
	i = v->size - (pr / 4) - 2;
	dc = (v->size - 1 - i) * 4;
	dc += ft_count_digits(v->nbr[v->size - 1]);
	ft_round_helper(v, pr, dc, i);
	return (v);
}

t_us				ft_vector_resize_r(t_v *v, size_t len)
{
	t_us	x[len];

	ft_clear_arr(x, len);
	ft_arrcpy(x, v->nbr, v->size);
	v->resize(v, len);
	ft_arrcpy(v->nbr, x, len);
	ft_clear_arr(x, len);
	ft_arrcpy(x, v->r_val, v->max_size - 1);
	ft_clear_arr(v->r_val, v->max_size - 1);
	free(v->r_val);
	v->r_val = NULL;
	if (!(v->r_val = (t_us*)malloc(sizeof(t_us) * len)))
		return (0);
	ft_arrcpy(v->r_val, x, len);
	v->size = len;
	v->max_size = len;
	return (1);
}
