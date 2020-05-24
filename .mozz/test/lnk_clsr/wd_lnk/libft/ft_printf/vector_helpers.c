/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 12:51:00 by tvanessa          #+#    #+#             */
/*   Updated: 2020/01/06 19:55:19 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					ft_vector_append(t_us d, t_v *v)
{
	if (!v)
		return (0);
	if (v->size >= v->max_size)
		return (0);
	v->nbr[v->size] = d;
	++(v->size);
	return (1);
}

t_v					*ft_vector_nbr_set(t_v *v, t_us *arr, t_us l)
{
	short	d;

	while (l && !arr[l - 1])
		--l;
	d = l;
	l = 0;
	if (v->point && d)
		while (!(arr[l++]) && (v->point -= 4) >= 0)
			--d;
	if (v->point < 0)
		v->point += 4;
	if (d != v->max_size)
		v->resize(v, (d ? d : 1));
	else
		v->size = 0;
	l = l ? l - 1 : 0;
	while (v->size < v->max_size)
	{
		v->nbr[v->size] = arr[l];
		++v->size;
		++l;
	}
	if (v->size == 1 && !v->nbr[0])
		v->point = 0;
	return (v);
}

size_t				ft_vector_count_digits(t_v *v)
{
	size_t	i;
	t_us	n;

	i = (v->size - 1) * 4;
	n = v->nbr[v->size - 1];
	while (n)
	{
		n /= 10;
		++i;
	}
	if (v->point >= (short)i)
		return (v->point + 1);
	return (i);
}
