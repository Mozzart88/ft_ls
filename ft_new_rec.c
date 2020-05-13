/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_rec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 19:50:11 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/13 05:49:14 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_get_path(t_rec *r, char *dst)
{
	ft_memset(dst, 0, __DARWIN_MAXPATHLEN);
	ft_strcpy(dst, r->path);
	// ft_strcat(dst, "/");
	ft_strcat(dst, r->name);
	return (dst);
}

char	*ft_get_lnk_path(t_rec *r, char *dst)
{
	ft_memset(dst, 0, __DARWIN_MAXPATHLEN);
	ft_strcpy(dst, r->lnk_path);
	// ft_strcat(dst, "/");
	// ft_strcat(dst, r->name);
	return (dst);
}

static char	*ft_get_dir(const char *path, char *dst)
{
	// ft_strncpy(dst, path, (ft_strrchr(path, '/') - path));
	char *path_end;

	path_end = ft_strrchr(path, '/');
	if (path_end)
	{
		ft_strncat(dst, path, (path_end - path));
		ft_strcat(dst, "/");
	}
	return (dst);
}

static char	*ft_get_name(const char *path, char *dst)
{
	// ft_strncpy(dst, path, (ft_strrchr(path, '/') - path));
	char *path_end;

	path_end = ft_strrchr(path, '/');
	if (path_end)
		ft_strcpy(dst, path_end + 1);
	else
		ft_strcpy(dst, path);
	return (dst);
}

t_rec		*ft_new_rec(t_de *de, char *name, char path[__DARWIN_MAXPATHLEN])
{
	t_rec	*r;
	char	p[__DARWIN_MAXPATHLEN];

	r = NULL;
	if (!(r = (t_rec*)malloc(sizeof(t_rec))))
		return (NULL);
	ft_memset(r->path, 0, __DARWIN_MAXPATHLEN);
	ft_get_dir(path, (r->path));
	ft_get_dir(name, (r->path));
	ft_get_name(name, (r->name));
	r->_errno = 0;
	if (de)
		r->de = ft_copyde(de);
	else
	{
		if (!(r->de = (t_de*)malloc(sizeof(t_de))))
			return (NULL);
		ft_strcpy(r->de->d_name, name);
	}
	if (!(r->st = (t_stat*)malloc(sizeof(t_stat))))
		return (NULL);
	ft_get_path(r, p);
	if (lstat(p, r->st))
    {
            r->_errno = errno;
            r->_errstr = strerror(errno);
    }
	ft_memset(r->xattrs, 0, __DARWIN_MAXPATHLEN);
	listxattr(p, r->xattrs, __DARWIN_MAXPATHLEN, XATTR_SHOWCOMPRESSION);
	if (!ft_strequ(r->xattrs, "com.apple.FinderInfo"))
		ft_memset(r->xattrs, 0, __DARWIN_MAXPATHLEN);
	ft_memset(r->lnk_path, 0, __DARWIN_MAXPATHLEN);
	if ((r->st->st_mode & S_IFMT) == S_IFLNK)
	{
		readlink(p, r->lnk_path, __DARWIN_MAXPATHLEN);
		r->lnk_to = ft_new_rec(NULL, r->lnk_path, r->path);
	}
	return (r);
}
