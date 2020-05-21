/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_rec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 19:50:11 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/21 13:51:54 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*ft_get_dir(const char *path, char *dst)
{
	char *path_end;

	path_end = ft_strrchr(path, '/');
	if (path_end)
	{
		ft_strncat(dst, path, (path_end - path));
		ft_strcat(dst, "/");
	}
	return (dst);
}

static char		*ft_get_name(const char *path, char *dst)
{
	char *path_end;

	path_end = ft_strrchr(path, '/');
	if (path_end)
		ft_strcpy(dst, path_end + 1);
	else
		ft_strcpy(dst, path);
	return (dst);
}

static t_rec	*ft_get_lnk(t_rec *rec, char file[__DARWIN_MAXPATHLEN])
{
	ft_bzero(rec->lnk_path, __DARWIN_MAXPATHLEN);
	if (ft_is_lnk(rec->st->st_mode))
	{
		readlink(file, rec->lnk_path, __DARWIN_MAXPATHLEN);
		return (ft_new_rec(rec->lnk_path, rec->path));
	}
	return (NULL);
}

static acl_t	ft_get_acl(char *p, mode_t mode)
{
	if (ft_is_lnk(mode))
		return (acl_get_link_np(p, ACL_TYPE_EXTENDED));
	else
		return (acl_get_file(p, ACL_TYPE_EXTENDED));
}

t_rec			*ft_new_rec(char *name, char path[__DARWIN_MAXPATHLEN])
{
	t_rec	*r;
	char	p[__DARWIN_MAXPATHLEN];

	r = NULL;
	if (!(r = (t_rec*)malloc(sizeof(t_rec))))
		return (NULL);
	ft_bzero(r->path, __DARWIN_MAXPATHLEN);
	ft_get_dir(path, (r->path));
	ft_get_dir(name, (r->path));
	ft_get_name(name, (r->name));
	r->err_no = 0;
	r->st = NULL;
	r->lnk_to = NULL;
	r->acl = NULL;
	if (!(r->st = (t_stat*)malloc(sizeof(t_stat))))
	{
		ft_destroy_rec((void**)&r);
		return (NULL);
	}
	ft_get_path(r, p);
	if (lstat(p, r->st))
	{
		free(r->st);
		r->st = NULL;
		r->err_no = errno;
		r->err_str = strerror(errno);
	}
	else
	{
		ft_bzero(r->xattrs, __DARWIN_MAXPATHLEN);
		listxattr(p, r->xattrs, XATTR_MAXNAMELEN, XATTR_NOFOLLOW);
		r->acl = ft_get_acl(p, r->st->st_mode);
		// if (ft_is_lnk(r->st->st_mode))
			r->lnk_to = ft_get_lnk(r, p);
	}
	return (r);
}
