/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 14:05:34 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/20 12:40:13 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_us	ft_read_params(t_vect *v, t_vect *p)
{
	t_rec	*r;
	t_us	i;

	i = 0;
	while (i < v->len)
	{
		r = NULL;
		if ((r = ft_new_rec((char*)*(p->arr), "")) == NULL)
			return (1);
		++p->arr;
		if (r && r->err_no)
		{
			ft_perr((char*)*(p->arr - 1), r->err_str);
			ft_destroy_rec((void**)&r);
			r = NULL;
			--v->len;
			continue;
		}
		v->arr[i] = r;
		++i;
	}
	p->arr = p->arr - p->len;
	p->len = i;
	return (0);
}

void		ft_ls(t_vect *p, uint32_t f)
{
	t_vect		*v;
	t_maxvallen	mvl;

	if (!(v = ft_new_vect(sizeof(t_rec), p->len, ft_destroy_rec)))
		return ;
	if ((ft_read_params(v, p)) == 1)
		exit(1);
	f |= FT_U_BITS;
	if (f & LF_FLAGS)
		mvl = ft_get_mvl(v, f);
	if (f & D_FLAG)
		ft_print_all(v, &f, mvl);
	else
	{
		ft_print_files(v, &f, mvl);
		ft_print_dirs(v, &f);
	}
	ft_destroy_vect(&v);
	return ;
}
