/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 11:00:33 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/21 18:24:36 by mozzart          ###   ########.fr       */
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
	d.len = 0;
	i = 0;
	while ((d.dirent = readdir(d.dir)) && ++i)
	{
		if (ft_is_hidden(f, d.dirent->d_name))
			continue ;
		d.content[d.len] = ft_new_rec(d.dirent->d_name, path);
		if (!d.content[d.len] || d.content[d.len]->err_no)
		{
			if (!d.content[d.len])
				continue;
			ft_perr(d.content[d.len]->name, d.content[d.len]->err_str);
			ft_destroy_rec((void**)&d.content[d.len]);
			d.content[d.len] = NULL;
		}
		else
			++d.len;
	}
	closedir(d.dir);
	if (!(v = ft_new_vect(sizeof(t_rec), d.len, ft_destroy_rec)))
		return (NULL);
	v->ilen = i;
	ft_arr_cpy(v->arr, (void**)d.content, d.len);
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
