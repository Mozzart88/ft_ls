/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 21:01:43 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/09 21:51:16 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_sort_by_name(t_ull a, t_ull b)
{
	t_rec	*ra;
	t_rec	*rb;
	char	an[__DARWIN_MAXPATHLEN];
	char	bn[__DARWIN_MAXPATHLEN];

	ra = (t_rec*)a;
	rb = (t_rec*)b;
	return (ft_strcmp(ft_get_path(ra, an), ft_get_path(rb, bn)));
}

static int	ft_sort_by_mtime(t_ull a, t_ull b)
{
	t_rec	*ra;
	t_rec	*rb;
	long	r;

	ra = (t_rec*)a;
	rb = (t_rec*)b;
	r = ra->st->st_mtimespec.tv_sec - rb->st->st_mtimespec.tv_sec;
	return (r);
}

static int	ft_sort_by_atime(t_ull a, t_ull b)
{
	t_rec	*ra;
	t_rec	*rb;

	ra = (t_rec*)a;
	rb = (t_rec*)b;
	return (ra->st->st_atimespec.tv_sec - rb->st->st_atimespec.tv_sec);
}
/* 
static void		ft_sort_by_type(t_rec **arr)
{
	if (arr || l)
		return ;
}
 */
void		ft_sort_by_size()
{
	return ;
}

void		ft_sort_recs(t_vect *arr, uint32_t f)
{

	ft_msort(arr, !(f & R_FLAG), ft_sort_by_name);
	if (f & T_FLAG)
	{
		if (f & U_FLAG)
			ft_msort(arr, f & R_FLAG, ft_sort_by_atime);
		else
			ft_msort(arr, f & R_FLAG, ft_sort_by_mtime);
	}
}
