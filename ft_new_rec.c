/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_rec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 19:50:11 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/22 04:24:18 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		ft_get_dir(const char *path, char *dst)
{
	char	*path_end;
	size_t	i;
	size_t	l;

	if (!path || !*path)
		return (0);
	i = 0;
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

	ft_bzero(p, __DARWIN_MAXPATHLEN);
	if (ft_is_lnk(rec->st->st_mode))
	{
		if (readlink(file, p, __DARWIN_MAXPATHLEN))
		{
			rec->lnk_path = ft_strdup(p);
			return (ft_new_rec(rec->lnk_path, ""));
		}
	}
	return (NULL);
}

t_rec			*ft_new_rec(char *name, char path[__DARWIN_MAXPATHLEN])
{
	t_rec	*r;
	char	p[__DARWIN_MAXPATHLEN];

	r = NULL;
	if (!(r = ft_new_clear_rec()))
		return (NULL);
	ft_bzero(p, __DARWIN_MAXPATHLEN);
	ft_get_dir(path, p);
	ft_get_dir(name, p);
	r->path = ft_strdup(p);
	ft_get_name(name, p);
	r->name = ft_strdup(p);
	if (!(r->st = (t_stat*)malloc(sizeof(t_stat))))
		return (ft_destroy_rec((void**)&r));
	ft_get_path(r, p);
	if (lstat(p, r->st))
		ft_st_error(r);
	else
	{
		ft_rec_set_x(r, p);
		r->lnk_to = ft_get_lnk(r, p);
	}
	return (r);
}
