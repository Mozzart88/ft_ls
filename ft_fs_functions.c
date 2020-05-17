/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fs_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 07:43:16 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/17 07:45:13 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			*ft_get_path(t_rec *r, char *dst)
{
	ft_memset(dst, 0, __DARWIN_MAXPATHLEN);
	ft_strcpy(dst, r->path);
	ft_strcat(dst, r->name);
	return (dst);
}

char			*ft_get_lnk_path(t_rec *r, char *dst)
{
	ft_memset(dst, 0, __DARWIN_MAXPATHLEN);
	ft_strcpy(dst, r->lnk_path);
	return (dst);
}
