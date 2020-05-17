/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_rifo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 10:21:10 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/17 10:41:05 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	m[10] = r->xattrs[0] ? '@' : '\0';
	m[11] = '\0';
	ft_printf("%-11s ", m);
}

static void	ft_print_time(t_time t)
{
	time_t		tl;
	t_datetime	dt;
	long long	dif_time;
	char		*f;

	tl = time(NULL);
	dt = ft_localtime(&t);
	dif_time = ft_difftime(&tl, &t.tv_sec);
	if (ft_strequ(getenv("LANG"), "ru_RU.UTF-8"))
	{
		f = "%2d %6s %02d:%02d ";
		if (dif_time < (31536000L / 2) && dif_time >= 0)
			ft_printf(f, dt.mday, dt.monstr, dt.hour, dt.min);
		else
			ft_printf("%2d %6s %-5 d ", dt.mday, dt.monstr, dt.year);
	}
	else
	{
		f = "%3s %2d %02d:%02d ";
		if (dif_time < (31536000L / 2) && dif_time > (31536000L / 2 * -1))
			ft_printf(f, dt.monstr, dt.mday, dt.hour, dt.min);
		else
			ft_printf("%3s %2d %-5 d ", dt.monstr, dt.mday, dt.year);
	}
}

static void	ft_print_filename(t_rec *r, t_us f)
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
	}
	ft_bzero(lp, __DARWIN_MAXPATHLEN);
	ft_printf("%s", f & 0x1000 ? ft_get_path(r, lp) : r->name);
	ft_bzero(lp, __DARWIN_MAXPATHLEN);
	if ((r->st->st_mode & S_IFMT) == S_IFLNK && (f & LF_FLAGS))
		ft_printf(" -> %s\n", ft_get_lnk_path(r, lp));
	else
		ft_printf("\n");
}

void		ft_print_rifo(t_rec *rd, uint32_t *f, t_maxvallen mvl)
{
	t_ull	offset;

	offset = mvl.sl < mvl.maj + mvl.min ? mvl.maj + mvl.min + 3 : mvl.sl;
	if (*f & LF_FLAGS)
	{
		ft_print_stat(rd);
		ft_printf("%* hu ", mvl.lnk, rd->st->st_nlink);
		if (!(*f & G_FLAG))
			ft_printf("%-*s ", mvl.un + 1, ft_get_user_name(rd->st->st_uid));
		ft_printf("%-*s ", mvl.gn + 1, ft_get_group_name(rd->st->st_gid));
		if (ft_is_spec(rd->st->st_mode))
		{
			offset = mvl.min < 3 ? 3 : mvl.min;
			ft_printf(" %*lld", mvl.maj, (rd->st->st_rdev >> 24) & 0377);
			ft_printf(", %*lld ", offset, rd->st->st_rdev & 0377);
		}
		else
			ft_printf("%*lld ", offset, rd->st->st_size);
		if (*f & U_FLAG)
			ft_print_time(rd->st->st_atimespec);
		else
			ft_print_time(rd->st->st_mtimespec);
	}
	ft_print_filename(rd, *f);
	*f &= 0xFFF;
}
