/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_rifo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 10:21:10 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/23 13:18:08 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	ft_get_xmode(acl_t acl, char *xattrs)
{
	char c;

	c = acl ? '+' : '\0';
	c = xattrs && xattrs[0] ? '@' : c;
	return (c);
}

static void	ft_print_stat(t_rec *r)
{
	int		i;
	int		j;
	char	m[12];
	char	*t;
	t_us	mask;

	t = "rwxrwxrwx";
	mask = S_ISUID;
	m[0] = ft_get_file_type(r->st->st_mode);
	i = 0;
	j = 1 << 9;
	while ((++i < 10) && (j >>= 1))
	{
		if (i % 3 == 0 && r->st->st_mode & mask)
		{
			m[i] = i == 9 ? 't' : 's';
			m[i] = r->st->st_mode & j ? m[i] : ft_toupper(m[i]);
		}
		else
			m[i] = r->st->st_mode & j ? t[i - 1] : '-';
		mask = i % 3 == 0 ? mask >> 1 : mask;
	}
	m[10] = ft_get_xmode(r->acl, r->xattrs);
	m[11] = '\0';
	ft_printf("%-11s ", m);
}

static void	ft_print_filename(t_rec *r, uint32_t f)
{
	char lp[__DARWIN_MAXPATHLEN];

	if (f & UG_FLAG)
	{
		if ((r->st->st_mode & S_IFMT) == S_IFDIR)
			ft_printf("\e[34m%s\e[0m", r->name);
		else if ((r->st->st_mode & S_IFMT) == S_IFCHR)
			ft_printf("\e[34;103m%s\e[0m", r->name);
		else if ((r->st->st_mode & S_IFMT) == S_IFBLK)
			ft_printf("\e[34;106m%s\e[0m", r->name);
		else if ((r->st->st_mode & S_IFMT) == S_IFLNK)
			ft_printf("\e[35m%s\e[0m", r->name);
		else if ((r->st->st_mode & 0111))
			ft_printf("\e[31m%s\e[0m", r->name);
		else
			ft_printf("%s", f & FT_F_BIT ? ft_get_path(r, lp) : r->name);
	}
	else
		ft_printf("%s", f & FT_F_BIT ? ft_get_path(r, lp) : r->name);
	if (f & P_FLAG && (r->st->st_mode & S_IFMT) == S_IFDIR)
		ft_printf("/");
	if ((r->st->st_mode & S_IFMT) == S_IFLNK && (f & LF_FLAGS))
		ft_printf(" -> %s", ft_get_lnk_path(r, lp));
	ft_printf("\n");
	ft_bzero(lp, __DARWIN_MAXPATHLEN);
}

static void	ft_print_ls_time(t_stat *st, uint32_t f)
{
	if (f & U_FLAG)
		ft_print_time(st->st_atime);
	else if (f & C_FLAG)
		ft_print_time(st->st_ctimespec);
	else if (f & UU_FLAG)
		ft_print_time(st->st_birthtimespec);
	else
		ft_print_time(st->st_mtimespec);
}

void		ft_print_rifo(t_rec *rd, uint32_t *f, t_maxvallen mvl)
{
	t_ull	offset;

	if (*f & LF_FLAGS)
	{
		offset = mvl.sl < mvl.maj + mvl.min ? mvl.maj + mvl.min + 3 : mvl.sl;
		ft_print_stat(rd);
		ft_printf("%* hu ", mvl.lnk, rd->st->st_nlink);
		ft_print_owners(rd->st, mvl, *f);
		if (ft_is_spec(rd->st->st_mode))
		{
			offset = mvl.min < 3 ? 3 : mvl.min;
			ft_printf(" %*lld", mvl.maj, (rd->st->st_rdev >> 24) & 0377);
			ft_printf(", %*lld ", offset, rd->st->st_rdev & 0377);
		}
		else
			ft_printf("%*lld ", offset, rd->st->st_size);
		ft_print_ls_time(rd->st, *f);
	}
	ft_print_filename(rd, *f);
	*f &= FT_ALL_FLAGS;
}
