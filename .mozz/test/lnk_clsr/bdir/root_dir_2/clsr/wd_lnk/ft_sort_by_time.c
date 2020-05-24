/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_by_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 17:18:39 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/18 17:46:23 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

long long	ft_sort_by_mtime(void *a, void *b)
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

long long	ft_sort_by_atime(void *a, void *b)
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

long long	ft_sort_by_ctime(void *a, void *b)
{
	t_rec	*ra;
	t_rec	*rb;
	long	r;

	ra = (t_rec*)a;
	rb = (t_rec*)b;
	r = rb->st->st_ctimespec.tv_sec - ra->st->st_ctimespec.tv_sec;
	if (!r)
		r = rb->st->st_ctimespec.tv_nsec - ra->st->st_ctimespec.tv_nsec;
	if (!r)
		r = ft_sort_by_name(a, b);
	return (r);
}

long long	ft_sort_by_utime(void *a, void *b)
{
	t_rec	*ra;
	t_rec	*rb;
	long	r;

	ra = (t_rec*)a;
	rb = (t_rec*)b;
	r = rb->st->st_birthtimespec.tv_sec - ra->st->st_birthtimespec.tv_sec;
	if (!r)
		r = rb->st->st_birthtimespec.tv_nsec - ra->st->st_birthtimespec.tv_nsec;
	if (!r)
		r = ft_sort_by_name(a, b);
	return (r);
}
