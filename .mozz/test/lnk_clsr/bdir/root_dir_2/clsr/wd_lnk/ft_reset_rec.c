/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset_rec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 03:55:54 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/22 04:28:23 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_rec			*ft_new_clear_rec(void)
{
	t_rec	*r;

	r = NULL;
	if (!(r = (t_rec*)malloc(sizeof(t_rec))))
		return (NULL);
	r->st = NULL;
	r->path = NULL;
	r->name = NULL;
	r->err_no = 0;
	r->err_str = NULL;
	r->xattrs = NULL;
	r->lnk_path = NULL;
	r->lnk_to = NULL;
	r->acl = NULL;
	return (r);
}

static acl_t	ft_get_acl(char *p, mode_t mode)
{
	if (ft_is_lnk(mode))
		return (acl_get_link_np(p, ACL_TYPE_EXTENDED));
	else
		return (acl_get_file(p, ACL_TYPE_EXTENDED));
}

void			ft_rec_set_x(t_rec *r, char *p)
{
	char	x[XATTR_MAXNAMELEN];

	r->acl = ft_get_acl(p, r->st->st_mode);
	ft_bzero(x, XATTR_MAXNAMELEN);
	if ((listxattr(p, x, XATTR_MAXNAMELEN, XATTR_NOFOLLOW)) > 0)
		r->xattrs = ft_strdup(x);
	return ;
}
