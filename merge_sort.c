/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 22:29:26 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/09 15:42:09 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_swap_pointers(t_ull *a, t_ull *b)
{
	t_ull	t;

	t = *a;
	*a = *b;
	*b = t;
	return;
}

static void	merge(t_vect *arr, t_vect *l, t_vect *r, t_us asc, int f(t_ull, t_ull))
{
	size_t		i;
	size_t		j;
	size_t		k;

	i = 0;
	j = 0;
	k = 0;
	while (i < l->len && j < r->len)
	{
		if ((f(l->arr[i], r->arr[j]) <= 0 && asc) || (f(l->arr[i], r->arr[j]) > 0 && !asc))
		{
			ft_swap_pointers(&arr->arr[k], &l->arr[i]);
			++i;
		}
		else
		{
			ft_swap_pointers(&arr->arr[k], &r->arr[j]);
			++j;
		}
		++k;
	}
	while (i < l->len)
	{
		ft_swap_pointers(&arr->arr[k], &l->arr[i]);
		++i;
		++k;
	}
	while (j < r->len)
	{
		ft_swap_pointers(&arr->arr[k], &r->arr[j]);
		++j;
		++k;
	}
	return;
}

int		ft_msort(t_vect *v, t_us asc, int f(t_ull, t_ull))
{
	// int	ll;
	// int	rl;
	size_t	i;
	t_vect *l;
	t_vect *r;

	if (v->len < 2)
		return (2);
	// ll = v->len / 2;
	// rl = v->len - ll;
	// if (!(l = ft_new_vect(v->arr, v->size, v->len / 2)))
	if (!(l = ft_new_vect(NULL, v->size, v->len / 2)))
		return (1);
	// if (!(r = ft_new_vect(&(v->arr[v->len / 2 + 1]), v->size, v->len - l->len)))
	if (!(r = ft_new_vect(NULL, v->size, v->len - l->len)))
	{
		ft_destroy_vect(l);
		return (1);
	}
	i = 0;
	while (i < l->len)
	{
		l->arr[i] = v->arr[i];
		++i;
	}
	i = 0;
	while (i < r->len)
	{
		r->arr[i] = v->arr[l->len + i];
		++i;
	}
	ft_msort(l, asc, f);
	ft_msort(r, asc, f);
	merge(v, l, r, asc, f);
	return (0);
}
