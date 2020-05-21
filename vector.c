/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 04:28:02 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/19 22:21:32 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_vect	*ft_new_vect(size_t s, size_t l, void f(void**))
{
	t_vect	*v;

	if (!(v = (t_vect*)malloc(sizeof(t_vect))))
		return (NULL);
	if (!(v->arr = (void**)malloc(sizeof(void*) * l)))
	{
		v = NULL;
		free(v);
	}
	v->size = s;
	v->len = l;
	v->ilen = l;
	v->is_sorted = 0;
	v->arr_destroier = f;
	return (v);
}

void	*ft_destroy_vect(t_vect **v)
{
	void *p;

	while ((*v)->len-- > 0)
	{
		if ((p = (void*)&((*v)->arr[(*v)->len])))
		// p = (void*)&((*v)->arr[(*v)->len]);
			if ((*v)->arr_destroier)
				(*v)->arr_destroier(p);
		(*v)->arr[(*v)->len] = NULL;
	}
	(*v)->size = 0;
	(*v)->len = 0;
	(*v)->ilen = 0;
	(*v)->is_sorted = 0;
	free(((*v)->arr));
	(*v)->arr = NULL;
	free((*v));
	(*v) = NULL;
	return (NULL);
}

void	ft_arr_cpy(void **dst, void **src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		++i;
	}
}
