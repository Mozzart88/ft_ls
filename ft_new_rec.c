/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_rec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 19:50:11 by tvanessa          #+#    #+#             */
/*   Updated: 2020/02/21 20:47:08 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_rec	*ft_new_rec(t_de *de, char *name, char path[__DARWIN_MAXPATHLEN])
{
	t_rec	*r;

	r = NULL;
	if (!(r = (t_rec*)malloc(sizeof(t_rec))))
		return (NULL);
	ft_memset(r->path, 0, __DARWIN_MAXPATHLEN);
	ft_strcat(r->path, path);
	ft_strcat(r->path, name);
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
	name = r->path[0] ? r->path : name;
	if (stat(name, r->st))
    {
            r->_errno = errno;
            r->_errstr = strerror(errno);
    }
	return (r);
}
