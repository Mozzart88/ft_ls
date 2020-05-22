/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destroy_rec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 21:33:49 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/22 04:13:56 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			*ft_destroy_rec(void **p)
{
	t_rec *r;

	if (!*p || !(r = *(t_rec**)p))
		return (NULL);
	if (r->lnk_to)
		ft_destroy_rec((void**)&r->lnk_to);
	if (r->st)
		free(r->st);
	r->st = NULL;
	r->err_no = 0;
	ft_strdel(&r->path);
	ft_strdel(&r->name);
	if (r->xattrs)
		ft_strdel(&r->xattrs);
	if (r->lnk_path)
		ft_strdel(&r->lnk_path);
	if (r->err_str)
		r->err_str = NULL;
	if (r->acl)
		acl_free((void*)r->acl);
	free(r);
	r = NULL;
	return (NULL);
}

void	*ft_st_error(t_rec *r)
{
		free(r->st);
		r->st = NULL;
		r->err_no = errno;
		r->err_str = strerror(errno);
		return (NULL);
}
