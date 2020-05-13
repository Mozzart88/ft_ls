/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 04:28:02 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/12 19:43:22 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_vect	*ft_new_vect(void *a, size_t s, size_t l)
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
	return (v);
}

void	*ft_destroy_vect(t_vect **v)
{
	(*v)->arr = NULL;
	(*v)->size = 0;
	(*v)->len = 0;
	(*v) = NULL;
	free(*v);
	return (NULL);
}
