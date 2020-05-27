/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 11:00:33 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/27 17:35:23 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static long		ft_count_dirents(char *dname, uint32_t f)
{
	size_t	i;
	DIR		*dir;
	t_de	*dirent;

	if ((dir = opendir(dname)) == NULL)
		return (-1);
	i = 0;
	while ((dirent = readdir(dir)))
	{
		if (ft_is_hidden(f, dirent->d_name))
			continue ;
		++i;
	}
	closedir(dir);
	return (i);
}

static void		ft_get_ents(DIR *dir, t_vect *v, uint32_t f, char *path)
{
	size_t	len;
	size_t	i;
	t_de	*dirent;
	t_rec	*r;

	i = 0;
	len = 0;
	while ((dirent = readdir(dir)) && ++i)
	{
		if (ft_is_hidden(f, dirent->d_name))
			continue ;
		if (!(r = ft_new_rec(dirent->d_name, path)) || r->err_no)
		{
			if (r->err_no)
			{
				ft_perr(r->name, r->err_str);
				ft_destroy_rec((void**)&r);
				v->arr[len] = NULL;
			}
			continue;
		}
		v->arr[len] = r;
		++len;
	}
	v->ilen = i;
}

static t_vect	*ft_opendir(char *dname, uint32_t f)
{
	t_vect		*v;
	char		path[__DARWIN_MAXPATHLEN];
	t_dir		d;

	if (!dname || dname[0] == 0x0)
		return (NULL);
	ft_bzero(path, __DARWIN_MAXPATHLEN);
	if (ft_strequ(dname, "/"))
		path[0] = '/';
	else
	{
		ft_strcpy(path, dname);
		path[ft_strlen(dname)] = '/';
	}
	if ((d.len = ft_count_dirents(dname, f)) < 0)
		return (NULL);
	if (!(v = ft_new_vect(d.len, ft_destroy_rec)))
		return (NULL);
	if ((d.dir = opendir(dname)) == NULL)
		return (NULL);
	d.len = 0;
	ft_get_ents(d.dir, v, f, path);
	closedir(d.dir);
	return (v);
}

int				ft_readdir(char *dname, uint32_t f)
{
	t_vect		*r;
	t_maxvallen mvl;

	if ((r = ft_opendir(dname, f)) == NULL)
		return (errno);
	ft_reset_mvl(&mvl);
	if (f & LF_FLAGS)
		mvl = ft_get_mvl(r, f);
	ft_print_all(r, &f, mvl);
	if (f & UR_FLAG)
		ft_print_dirs(r, &f);
	ft_destroy_vect(&r);
	return (0);
}
