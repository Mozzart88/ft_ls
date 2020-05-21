/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 11:00:33 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/22 02:11:27 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_vect	*ft_opendir(char *dname, uint32_t f)
{
	t_vect		*v;
	char		path[__DARWIN_MAXPATHLEN];
	t_dir		d;
	size_t		i;

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
	if ((d.dir = opendir(dname)) == NULL)
		return (NULL);
	i = 0;
	while ((d.dirent = readdir(d.dir)))
	{
		if (ft_is_hidden(f, d.dirent->d_name))
			continue ;
		++i;
	}
	closedir(d.dir);
	if (!(v = ft_new_vect(/* sizeof(t_rec),  */i, ft_destroy_rec)))
		return (NULL);
	if ((d.dir = opendir(dname)) == NULL)
		return (NULL);
	i = 0;
	d.len = 0;
	while ((d.dirent = readdir(d.dir)) && ++i)
	{
		if (ft_is_hidden(f, d.dirent->d_name))
			continue ;
		v->arr[d.len] = ft_new_rec(d.dirent->d_name, path);
		if (!v->arr[d.len] || ((t_rec*)(v->arr[d.len]))->err_no)
		{
			if (!v->arr[d.len])
				continue;
			ft_perr(((t_rec*)(v->arr[d.len]))->name, ((t_rec*)(v->arr[d.len]))->err_str);
			ft_destroy_rec((void**)&v->arr[d.len]);
			v->arr[d.len] = NULL;
		}
		else
			++d.len;
	}
	closedir(d.dir);
	v->ilen = i;
	// ft_arr_cpy(v->arr, (void**)d.content, d.len);
	return (v);
}

int				ft_readdir(char *dname, uint32_t f)
{
	t_vect		*r;
	t_maxvallen mvl;

	if ((r = ft_opendir(dname, f)) == NULL)
		return (errno);
	mvl = ft_get_mvl(r, f);
	ft_print_all(r, &f, mvl);
	if (f & UR_FLAG)
		ft_print_dirs(r, &f);
	ft_destroy_vect(&r);
	return (0);
}
