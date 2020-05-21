/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fs_filetype.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 09:53:00 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/21 13:39:01 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	ft_get_file_type(mode_t m)
{
	mode_t r;

	r = m & S_IFMT;
	if (r == S_IFIFO)
		return ('p');
	if (r == S_IFCHR)
		return ('c');
	if (r == S_IFDIR)
		return ('d');
	if (r == S_IFBLK)
		return ('b');
	if (r == S_IFLNK)
		return ('l');
	if (r == S_IFSOCK)
		return ('s');
	return ('-');
}

// t_us	ft_is_dir(mode_t m)
t_us	ft_is_dir(t_rec *m)
{
	if (!m || !m->st || !m->st->st_mode)
		return (0);
	if (m->st->st_mode && ((m->st->st_mode & S_IFMT) == S_IFDIR))
		return (1);
	return (0);
}

t_us	ft_is_spec(mode_t m)
{
	if ((m & S_IFMT) == S_IFSOCK)
		return (1);
	if ((m & S_IFMT) == S_IFWHT)
		return (1);
	if ((m & S_IFMT) == S_IFBLK)
		return (1);
	if ((m & S_IFMT) == S_IFCHR)
		return (1);
	if ((m & S_IFMT) == S_IFIFO)
		return (1);
	return (0);
}

t_us	ft_is_lnk(mode_t m)
{
	if ((m & S_IFMT) == S_IFLNK)
		return (1);
	return (0);
}

t_us	ft_is_reg_file(mode_t m)
{
	if ((m & S_IFMT) == S_IFREG)
		return (1);
	return (0);
}
