/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 22:29:26 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/16 22:41:46 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_swap_pointers(void **a, void **b)
{
	void	*t;

	t = *a;
	*a = *b;
	*b = t;
	return ;
}

static void	merge(t_vect *a[3], t_us asc, long long f(void *, void *))
{
	size_t		i;
	size_t		j;
	size_t		k;

	i = 0;
	j = 0;
	k = 0;
	while (i < a[1]->len && j < a[2]->len)
	{
		if ((asc && f(a[1]->arr[i], a[2]->arr[j]) > 0) ||\
		(!asc && f(a[1]->arr[i], a[2]->arr[j]) < 0))
			ft_swap_pointers(&a[0]->arr[k], &a[1]->arr[i++]);
		else
			ft_swap_pointers(&a[0]->arr[k], &a[2]->arr[j++]);
		++k;
	}
	while (i < a[1]->len)
		ft_swap_pointers(&a[0]->arr[k++], &a[1]->arr[i++]);
	while (j < a[2]->len)
		ft_swap_pointers(&a[0]->arr[k++], &a[2]->arr[j++]);
	return ;
}

int			ft_msort(t_vect *v, t_us asc, long long f(void *, void *))
{
	t_vect	*a[3];

	if (v->len < 2)
		return (2);
	if (!(a[1] = ft_new_vect(v->size, v->len / 2, NULL)))
		return (1);
	if (!(a[2] = ft_new_vect(v->size, v->len - a[1]->len, NULL)))
	{
		ft_destroy_vect(&a[1]);
		return (1);
	}
	ft_arr_cpy(a[1]->arr, v->arr, a[1]->len);
	ft_arr_cpy(a[2]->arr, (v->arr + a[1]->len), a[2]->len);
	a[0] = v;
	ft_msort(a[1], asc, f);
	ft_msort(a[2], asc, f);
	merge(a, asc, f);
	ft_destroy_vect(&a[1]);
	ft_destroy_vect(&a[2]);
	return (0);
}
