/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 12:46:08 by tvanessa          #+#    #+#             */
/*   Updated: 2020/01/06 19:55:19 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				*ft_vector_destroy(t_v *v)
{
	if (!v)
		return (NULL);
	if (v->nbr)
	{
		ft_clear_arr(v->nbr, v->max_size);
		free(v->nbr);
		v->nbr = NULL;
	}
	if (v->r_val)
	{
		ft_clear_arr(v->r_val, v->max_size);
		free(v->r_val);
		v->r_val = NULL;
	}
	v->max_size = 0;
	v->size = 0;
	v->point = 0;
	v->append = NULL;
	v->destroy = NULL;
	v->add_to = NULL;
	v->resize = NULL;
	v->nbr_set = NULL;
	v->add = NULL;
	free(v);
	return ((v = NULL));
}

t_v					*ft_create_vector(size_t len)
{
	t_v	*v;

	if (len + 1 < len)
		return (NULL);
	if (!(v = (t_v*)malloc(sizeof(t_v))))
		return (NULL);
	v->destroy = ft_vector_destroy;
	if (!(v->nbr = (t_us*)malloc(sizeof(t_us) * len)))
		return (v->destroy(v));
	ft_clear_arr(v->nbr, len);
	v->r_val = NULL;
	v->append = ft_vector_append;
	v->add_to = ft_vector_addition_by_index;
	v->add_to_r = ft_vector_addition_by_index_r;
	v->add = ft_vector_addition;
	v->resize = ft_vector_resize;
	v->resize_r = ft_vector_resize_r;
	v->to_str = ft_vector_to_str;
	v->nbr_set = ft_vector_nbr_set;
	v->dcount = ft_vector_count_digits;
	v->max_size = len;
	v->size = 0;
	v->point = 0;
	v->neg = 0;
	return (v);
}

t_v					*ft_make_vector(size_t len, t_us int_val)
{
	t_v	*v;

	if (!(v = ft_create_vector(len)))
		return (NULL);
	if (!(v->append(int_val, v)))
		return (NULL);
	return (v);
}

t_v					*ft_make_long_vector(t_ull int_val)
{
	t_v		*v;
	t_ull	i;
	t_us	len;

	i = int_val ? int_val : 1;
	len = 0;
	while (i)
	{
		i /= 10000;
		++len;
	}
	if (!(v = ft_create_vector(len)))
		return (NULL);
	while ((v->size < v->max_size))
	{
		i = int_val % 10000;
		int_val /= 10000;
		if (!(v->append(i, v)))
			return (NULL);
	}
	return (v);
}

t_us				ft_vector_resize(t_v *v, size_t len)
{
	ft_clear_arr(v->nbr, v->size);
	free(v->nbr);
	v->nbr = NULL;
	if (!(v->nbr = (t_us*)malloc(sizeof(t_us) * len)))
		return (0);
	v->size = 0;
	v->max_size = len;
	return (1);
}
