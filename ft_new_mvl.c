/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_mvl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 11:54:10 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/17 11:54:32 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_maxvallen	ft_new_mvl(t_vect *v, uint32_t f)
{
	size_t		i;
	t_maxvallen mvl;
	t_maxvallen cvl;
	t_rec		*r;
	char		*names[2];

	mvl.gn = 0;
	mvl.un = 0;
	mvl.lnk = 0;
	mvl.sl = 0;
	mvl.maj = 0;
	mvl.min = 0;
	i = 0;
	while (i < v->len)
	{
		r = (t_rec*)v->arr[i];
		if (r->name[0] != '.' || (f & AE_FLAGS) || (f & 0x1000))
		{
			cvl.lnk = ft_count_digits(r->st->st_nlink);
			cvl.sl = ft_count_digits(r->st->st_size);
			cvl.maj = ft_count_digits((r->st->st_rdev >> 24) & 0377);
			cvl.min = ft_count_digits(r->st->st_rdev & 0377);
			names[0] = ft_get_group_name(r->st->st_gid);
			names[1] = ft_get_user_name(r->st->st_uid);
			cvl.gn = ft_strlen(names[0]);
			cvl.un = ft_strlen(names[1]);
			if (cvl.lnk > mvl.lnk)
				mvl.lnk = cvl.lnk;
			if (cvl.sl > mvl.sl)
				mvl.sl = cvl.sl;
			if (cvl.gn > mvl.gn)
				mvl.gn = cvl.gn;
			if (cvl.un > mvl.un)
				mvl.un = cvl.un;
			if (ft_is_spec(r->st->st_mode))
			{
				if (cvl.maj > mvl.maj)
					mvl.maj = cvl.maj;
				if (cvl.min > mvl.min)
					mvl.min = cvl.min;
			}
			ft_strdel(&(names[0]));
			ft_strdel(&(names[1]));
		}
		++i;
	}
	return (mvl);
}
