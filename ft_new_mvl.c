/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_mvl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 11:54:10 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/26 19:18:09 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_set_mvl(t_maxvallen *cvl, t_maxvallen *mvl, mode_t mode)
{
	if (cvl->lnk > mvl->lnk)
		mvl->lnk = cvl->lnk;
	if (cvl->sl > mvl->sl)
		mvl->sl = cvl->sl;
	if (cvl->gn > mvl->gn)
		mvl->gn = cvl->gn;
	if (cvl->un > mvl->un)
		mvl->un = cvl->un;
	if (cvl->name > mvl->name)
		mvl->name = cvl->name;
	if (ft_is_spec(mode))
	{
		if (cvl->maj > mvl->maj)
			mvl->maj = cvl->maj;
		if (cvl->min > mvl->min)
			mvl->min = cvl->min;
	}
}

static void	ft_set_cvl(t_maxvallen *cvl, t_rec *r, uint32_t ugi)
{
	char		*names[2];

	cvl->lnk = ft_count_digits(r->st->st_nlink);
	cvl->sl = ft_count_digits(r->st->st_size);
	cvl->maj = ft_count_digits((r->st->st_rdev >> 24) & 0377);
	cvl->min = ft_count_digits(r->st->st_rdev & 0377);
	cvl->name = ft_strlen(r->name);
	if (ugi)
	{
		cvl->gn = ft_count_digits(r->st->st_gid);
		cvl->un = ft_count_digits(r->st->st_uid);
	}
	else
	{
		names[0] = ft_get_group_name(r->st->st_gid);
		names[1] = ft_get_user_name(r->st->st_uid);
		cvl->gn = ft_strlen(names[0]);
		cvl->un = ft_strlen(names[1]);
		ft_strdel(&(names[0]));
		ft_strdel(&(names[1]));
	}
}

static void	ft_reset_mvl(t_maxvallen *mvl)
{
	mvl->gn = 0;
	mvl->un = 0;
	mvl->lnk = 0;
	mvl->sl = 0;
	mvl->maj = 0;
	mvl->min = 0;
	mvl->name = 0;
}

t_maxvallen	ft_get_mvl(t_vect *v, uint32_t f)
{
	size_t		i;
	t_maxvallen mvl;
	t_maxvallen cvl;
	t_rec		*r;
	t_us		p;

	ft_reset_mvl(&mvl);
	i = 0;
	while (i < v->len)
	{
		r = (t_rec*)v->arr[i];
		p = ft_is_hidden(f, r->name);
		if (f & FT_ZP_BIT && ft_is_dir(r) && !(f & D_FLAG))
			p = 1;
		if (!p)
		{
			ft_set_cvl(&cvl, r, f & N_FLAG);
			ft_set_mvl(&cvl, &mvl, r->st->st_mode);
		}
		++i;
	}
	return (mvl);
}
