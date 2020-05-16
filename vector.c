/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 04:28:02 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/16 15:10:41 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_vect	*ft_new_vect(void **a, size_t s, size_t l, void f(void**))
{
	t_vect	*v;
	// size_t	i;
	void 	*arr[l];

	if (!(v =(t_vect*)malloc(sizeof(t_vect))))
		return (NULL);
	
	if (a)
		;
	// {
	// 	i = 0;
	// 	while (i < l)
	// 	{
	// 		arr[i] = *(a + (i * s / 8));
	// 	// 	// v->arr[i] = a[]i];
	// 		++i;
	// 	}

	// }
	// v->arr = arr;
	// if (!(v->arr = (void**)malloc(sizeof(void*) * l)))
	// {
	// 	free(v);
	// 	v = NULL;
	// 	return (v);
	// }
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
		p = (*v)->arr[(*v)->len];
		if ((*v)->arr_destroier)
			(*v)->arr_destroier((void*)&p);
		p = NULL;
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

void	*ft_soft_destroy_vect(t_vect **v)
{
	(*v)->size = 0;
	(*v)->len = 0;
	(*v)->ilen = 0;
	(*v)->is_sorted = 0;
	free((*v));
	(*v) = NULL;
	return (NULL);
}
