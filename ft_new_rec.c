/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_rec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 19:50:11 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/17 15:41:07 by mozzart          ###   ########.fr       */
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

t_rec			*ft_new_rec(char *name, char path[__DARWIN_MAXPATHLEN])
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
	r->err_no = 0;
	if (!(r->st = (t_stat*)malloc(sizeof(t_stat))))
		return (NULL);
	ft_get_path(r, p);
	if (lstat(p, r->st))
	{
		r->err_no = errno;
		r->err_str = strerror(errno);
	}
	ft_memset(r->xattrs, 0, __DARWIN_MAXPATHLEN);
	listxattr(p, r->xattrs, __DARWIN_MAXPATHLEN, XATTR_SHOWCOMPRESSION);
	if (!ft_strequ(r->xattrs, "com.apple.FinderInfo"))
		ft_memset(r->xattrs, 0, __DARWIN_MAXPATHLEN);
	r->lnk_to = ft_get_lnk(r, p);
	return (r);
}

void			ft_destroy_rec(void **p)
{
	t_rec **v;

	v = (t_rec**)p;
	if ((*v)->st)
		free((*v)->st);
	(*v)->st = NULL;
	(*v)->err_no = 0;
	ft_bzero((*v)->path, __DARWIN_MAXPATHLEN);
	ft_bzero((*v)->name, __DARWIN_MAXPATHLEN);
	ft_bzero((*v)->xattrs, __DARWIN_MAXPATHLEN);
	ft_bzero((*v)->lnk_path, __DARWIN_MAXPATHLEN);
	free((*v)->err_str);
	(*v)->err_str = NULL;
	if ((*v)->lnk_to)
		ft_destroy_rec((void**)&(*v)->lnk_to);
	free(*v);
	*v = NULL;
}
