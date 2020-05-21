/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_rec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 19:50:11 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/22 02:27:27 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		ft_get_dir(const char *path, char *dst)
{
	char 	*path_end;
	size_t	i;
	size_t	l;

	if (!path || !*path )
		return (0);
	i = 0;
	// path_end = ft_strrchr(path, '/');
	l = ft_strlen(dst);
	if ((path_end = ft_strrchr(path, '/')))
	{
		i = (path_end - path);
		ft_strncpy(dst + l, path, i);
		dst[i] = '/';
		++i;
	}
	return (i + l);
}

static int		ft_get_name(const char *path, char *dst)
{
	char	*path_end;
	size_t	i;

	if (!path || !*path || !dst)
		return (0);
	i = 0;
	// path_end = ft_strrchr(path, '/');
	if ((path_end = ft_strrchr(path, '/')))
		ft_strcpy(dst, path_end + 1);
	else
		ft_strcpy(dst, path);
	i = ft_strlen(dst);
	return (i);
}

static t_rec	*ft_get_lnk(t_rec *rec, char file[__DARWIN_MAXPATHLEN])
{
	char p[__DARWIN_MAXPATHLEN];
	// ft_bzero(rec->lnk_path, __DARWIN_MAXPATHLEN);
	ft_bzero(p, __DARWIN_MAXPATHLEN);
	if (ft_is_lnk(rec->st->st_mode))
	{
		if (readlink(file, p, __DARWIN_MAXPATHLEN))
		{
			rec->lnk_path = ft_strdup(p);
			return (ft_new_rec(rec->lnk_path, ""));
		}
		// return (ft_new_rec(rec->lnk_path, rec->path));
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
	char	x[XATTR_MAXNAMELEN];
	// ssize_t	l;

	r = NULL;
	if (!(r = (t_rec*)malloc(sizeof(t_rec))))
		return (NULL);
	ft_bzero(p, __DARWIN_MAXPATHLEN);
	ft_get_dir(path, p);
	ft_get_dir(name, p);
	r->path = ft_strdup(p);
	// if (ft_get_name(name, p))
	ft_get_name(name, p);
	r->name = ft_strdup(p);
	r->err_no = 0;
	r->err_str = NULL;
	r->st = NULL;
	r->lnk_to = NULL;
	r->lnk_path = NULL;
	r->acl = NULL;
	r->xattrs = NULL;
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
		// r->err_str = ft_strdup(strerror(errno));
		r->err_str = strerror(errno);
	}
	else
	{
		r->acl = ft_get_acl(p, r->st->st_mode);
		ft_bzero(x, XATTR_MAXNAMELEN);
		// l = listxattr(p, x, XATTR_MAXNAMELEN, XATTR_NOFOLLOW);
		if ((listxattr(p, x, XATTR_MAXNAMELEN, XATTR_NOFOLLOW)) > 0)
			r->xattrs = ft_strdup(x);
		// if (ft_is_lnk(r->st->st_mode))
			r->lnk_to = ft_get_lnk(r, p);
	}
	return (r);
}
