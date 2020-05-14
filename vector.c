/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 04:28:02 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/15 00:13:55 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_vect	*ft_new_vect(void *a, size_t s, size_t l, void f(void**))
{
	t_vect	*v;
	size_t	i;
	char 	*arr;

	if (!(v =(t_vect*)malloc(sizeof(t_vect))))
		return (NULL);
	
	if (!(v->arr = (t_ull*)malloc(sizeof(t_ull) * l)))
	{
		v = NULL;
		free(v);
	}
	arr = (char*)a;
	if (a)
	{
		i = 0;
		while (i < l)
		{
			v->arr[i] = (t_ull)(arr + (i * s));
			++i;
		}

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
		p = (void*)&((*v)->arr[(*v)->len]);
		if ((*v)->arr_destroier)
			(*v)->arr_destroier((void*)&((*v)->arr[(*v)->len]));
		(*v)->arr[(*v)->len] = 0;
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
