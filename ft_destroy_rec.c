/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destroy_rec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 21:33:49 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/17 21:34:27 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_destroy_rec(void **p)
{
	t_rec *r;

	r = *(t_rec**)p;
	if (r->st)
		free(r->st);
	r->st = NULL;
	r->err_no = 0;
	ft_bzero(r->path, __DARWIN_MAXPATHLEN);
	ft_bzero(r->name, __DARWIN_MAXPATHLEN);
	ft_bzero(r->xattrs, XATTR_MAXNAMELEN);
	ft_bzero(r->lnk_path, __DARWIN_MAXPATHLEN);
	free(r->err_str);
	r->err_str = NULL;
	if (r->lnk_to)
		ft_destroy_rec((void**)&r->lnk_to);
	if (r->acl)
		acl_free((void*)r->acl);
	free(r);
	r = NULL;
}
