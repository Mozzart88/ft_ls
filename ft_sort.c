/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 21:01:43 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/15 20:59:09 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static long long	ft_sort_by_name(void *a, void *b)
{
	t_rec	*ra;
	t_rec	*rb;
	char	an[__DARWIN_MAXPATHLEN];
	char	bn[__DARWIN_MAXPATHLEN];

	ra = (t_rec*)a;
	rb = (t_rec*)b;
	return (ft_strcmp(ft_get_path(ra, an), ft_get_path(rb, bn)));
}

static long long	ft_sort_by_mtime(void *a, void *b)
{
	t_rec	*ra;
	t_rec	*rb;
	long	r;

	ra = (t_rec*)a;
	rb = (t_rec*)b;
	r = rb->st->st_mtimespec.tv_sec - ra->st->st_mtimespec.tv_sec;
	if (!r)
		r = rb->st->st_mtimespec.tv_nsec - ra->st->st_mtimespec.tv_nsec;
	if (!r)
		r = ft_sort_by_name(a, b);
	return (r);
}

static long long	ft_sort_by_atime(void *a, void *b)
{
	t_rec	*ra;
	t_rec	*rb;
	long	r;

	ra = (t_rec*)a;
	rb = (t_rec*)b;
	r = rb->st->st_atimespec.tv_sec - ra->st->st_atimespec.tv_sec;
	if (!r)
		r = rb->st->st_atimespec.tv_nsec - ra->st->st_atimespec.tv_nsec;
	if (!r)
		r = ft_sort_by_name(a, b);
	return (r);
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
	if (f & F_FLAG)
		return ;
	ft_msort(arr, f & R_FLAG, ft_sort_by_name);
	if (f & T_FLAG)
	{
		if (f & U_FLAG)
			ft_msort(arr, f & R_FLAG, ft_sort_by_atime);
		else
			ft_msort(arr, f & R_FLAG, ft_sort_by_mtime);
	}
	arr->is_sorted = f & 0xFFF;
}
