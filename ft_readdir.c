/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 11:00:33 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/17 11:45:34 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_vect	*ft_opendir(char *dname)
{
	t_vect		*v;
	char		path[__DARWIN_MAXPATHLEN];
	t_dir		d;

	ft_bzero(path, __DARWIN_MAXPATHLEN);
	ft_strcpy(path, dname);
	ft_strcat(path, "/");
	if ((d.dir = opendir(dname)) == NULL)
		return (NULL);
	d.len = 0;
	while ((d.dirent = readdir(d.dir)))
	{
		d.contrect[d.len] = ft_new_rec(d.dirent->d_name, path);
		++d.len;
	}
	closedir(d.dir);
	if (!(v = ft_new_vect(sizeof(t_rec), d.len, ft_destroy_rec)))
		return (NULL);
	ft_arr_cpy(v->arr, (void**)d.contrect, d.len);
	return (v);
}

int				ft_readdir(char *dname, uint32_t f)
{
	t_vect		*r;
	t_maxvallen mvl;

	if ((r = ft_opendir(dname)) == NULL)
		return (errno);
	mvl = ft_new_mvl(r, f);
	ft_print_all(r, &f, mvl);
	if (f & UR_FLAG)
		ft_print_dirs(r, &f);
	ft_destroy_vect(&r);
	return (0);
}
