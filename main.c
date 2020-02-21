/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 22:30:02 by tvanessa          #+#    #+#             */
/*   Updated: 2020/02/21 21:41:38 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

uint32_t	ft_get_flags(char **av, int *len)
{
	char		*ai;
	uint32_t	r;

	r = 0;
	while (--*len)
	{
		if (*av[0] != '-' && STRICT_FLAGS_ORDER)
			break;
		++*av;
		while (**av)
		{
			if ((ai = ft_strchr(LETER_FLAGS, **av)))
				r |= (1 << (ai - LETER_FLAGS));
				// arr[ai - LETER_FLAGS] = **av;
			else
			{
				ft_printf("Undefined flag %c passed!\n", **av);
				exit (-1);
			}
			++*av;
			// r <<= 1;
		}
		++av;
	}
	return (r);
}

void	ft_get_params(char **arr, char **av, int len)
{
	int	i;

	i = 0;
	while (len--)
	{
		if (*av[0] == '-' && STRICT_FLAGS_ORDER)
			break;
		arr[i] = *av;
		++av;
		++i;	
	}
	arr[i] = NULL;
}

t_de	*ft_copyde(t_de *de)
{
	t_de	*r;

	if (!(r = (t_de*)malloc(sizeof(t_de))))
		return (NULL);
	r->d_ino = de->d_ino;
	ft_strcpy(r->d_name, de->d_name);
	r->d_namlen = de->d_namlen;
	r->d_reclen = de->d_reclen;
	r->d_seekoff = de->d_seekoff;
	r->d_type = de->d_type;
	return (r);
}


char	ft_get_file_type(mode_t m)
{
	mode_t r;

	r = m & S_IFMT;
	if (r == S_IFDIR)
		return ('d');
	if (r == S_IFCHR)
		return ('c');
	if (r == S_IFBLK)
		return ('b');
	if (r == S_IFREG)
		return ('-');
	if (r == S_IFLNK)
		return ('l');
	if (r == S_IFSOCK)
		return ('s');
	return ('-');
}

void	ft_print_stat(mode_t mode)
{
	// t_stat	*st;
	int		i;
	int		j;
	char	m[11];
	char	*t;

	t = "rwxrwxrwx";
	m[0] = ft_get_file_type(mode);
	i = 1;
	j = 1 << 8;
	while (i < 10)
	{
		m[i] = mode & j ? t[i - 1] : '-';
		++i;
		j >>= 1;
	}
	m[10] = '\0';
	ft_printf("%s", m);
}

void	ft_print_user(uid_t id)
{
	t_pwd *p;
	if (!id)
		return ;
	if (!(p = getpwuid(id)))
		return ;
	ft_printf("%9s", p->pw_name);
	// free(p);
}

void	ft_print_group(gid_t id)
{
	t_grp *g;
	if (!id)
		return ;
	if (!(g = getgrgid(id)))
		return ;
	ft_printf("%6s", g->gr_name);
}

void		ft_get_month_str(char *arr[12])
{
	t_us	i;

	i = 0;
	while (i < 12)
	{
		if (i == 0)
			arr[i] = "Jan";
		else if (i == 1)
			arr[i] = "Feb";
		else if (i == 2)
			arr[i] = "Mar";
		else if (i == 3)
			arr[i] = "Apr";
		else if (i == 4)
			arr[i] = "May";
		else if (i == 5)
			arr[i] = "Jun";
		else if (i == 6)
			arr[i] = "Jul";
		else if (i == 7)
			arr[i] = "Aug";
		else if (i == 8)
			arr[i] = "Sep";
		else if (i == 9)
			arr[i] = "Oct";
		else if (i == 10)
			arr[i] = "Nov";
		else if (i == 11)
			arr[i] = "Des";
		++i;
	}
	
}

t_datetime	*ft_new_dt()
{
	t_datetime *r;

	if (!(r = (t_datetime*)malloc(sizeof(t_datetime))))
		return (NULL);
	r->day = 0;
	r->sec = 0;
	r->min = 0;
	r->mon = 0;
	r->hour = 0;
	r->year = 0;
	ft_get_month_str(r->monstr);
	return (r);
}

t_datetime	*ft_ctime(const time_t *t)
{
	t_datetime	*r;
	t_ull		days;

	r = NULL;
	r = ft_new_dt();
	r->year = (*t / 31536000L + 1970);
	days = (*t / 86400) - ((r->year - 1970) * 365 + ((r->year - 1970) / 4));
	// r->hour = (t_ull)((*t % 86400 / 3600));
	r->min = ((*t % 86400 % 3600 / 60));
	r->sec = (*t % 86400 % 3600 % 60);
	// r->min = (t_ull)((*t / 60) % 60);
	r->hour = (*t / 3600 * 3600);
	r->hour = *t - r->hour;
	r->hour /= 3600;
	r->mon = ((*t / 2678400L) % 12 - 1);
	r->day = (*t / 86400);
	if (r->year % 4)
		// r->day = (*t / 31536000L);
		// r->day %= 365;
		days += 1;
	else
		// r->day = (*t / 31622400L);
		r->day %= 366;
	// if (r->mon == 1 && r->year % 4)
	// 	r->day %= 28;
	// else if (r->mon == 1 && !(r->year % 4))
	// 	r->day %= 29;
	// else if (r->mon < 7 && r->mon % 2)
	// 	r->day %= 31;
	// else if (r->mon < 7 && !(r->mon % 2))
	// 	r->day %= 30;
	// else if (r->mon % 2)
	// 	r->day %= 31;
	// else
	// 	r->day %= 30;
	// ft_printf("%llu", **t / 31536000 + 1970);
	return (r);
}

void	ft_print_time(t_time t)
{
	char	*ct;
	char	**rd;
	char	**rt;
	// t_datetime *dt;

	// dt = ft_ctime(&t.tv_sec);
	ct = ctime(&t.tv_sec);
	rd = ft_strsplit(ct, ' ');
	rt = ft_strsplit(rd[3], ':');
	// ft_printf(" %s %hu %hu:%hu", dt->monstr[dt->mon], dt->day, dt->hour, dt->min);
	ft_printf(" %s %s %s:%s", rd[1], rd[2], rt[0], rt[1]);
}

void	ft_print_filename(t_rec *r, t_us color)
{
	if (!color)
		ft_printf(" %s\n", r->de->d_name);
	else
	{
		if (r->de->d_type == 4)
			ft_printf(" \e[34m%s\e[0m\n", r->de->d_name);
		else if (r->st->st_mode & 0b1001001)
			ft_printf(" \e[31m%s\e[0m\n", r->de->d_name);
		else
			ft_printf(" %s\n", r->de->d_name);
	}
}

void	ft_printdir(t_rec **rd, uint32_t f)
{
	t_us	i;

	i = 0;
	if (!*rd)
	 return ;
	if (f & 0b100000)
	{
		ft_print_stat((*rd)->st->st_mode);
		ft_printf("%5 hu", (*rd)->st->st_nlink);
		if (!(f & 0b1000))
			ft_print_user((*rd)->st->st_uid);
		ft_print_group((*rd)->st->st_gid);
		ft_printf("%7 lld", (*rd)->st->st_size);
		if (f & 0b1000000000)
			ft_print_time((*rd)->st->st_atimespec);
		else
			ft_print_time((*rd)->st->st_mtimespec);
	}
	ft_print_filename(*rd, f & 0b10000);
	if (*(rd + 1))
		ft_printdir(rd + 1, f);
}

void	ft_dir_sort(t_rec **d, uint32_t f)
{
	if (d && f)
		return ;
}

void	ft_print_total_blocks(t_rec **rd)
{
	blkcnt_t	bc;

	bc = 0;
	while (*rd)
	{
		bc += (*rd)->st->st_blocks;
		++rd;
	}
	ft_printf("total %lld\n", bc);
}

void	ft_readdir(char *dname, uint32_t flags)
{
	DIR		*d;
	t_de	*dc;
	t_rec	*rd[512];
	t_us	i;
	char	path[__DARWIN_MAXPATHLEN];

	i = 0;
	ft_memset(path, 0, __DARWIN_MAXPATHLEN);
	ft_strcpy(path, dname);
	ft_strcat(path, "/");
	if (!(flags & 0b10) && (d = opendir(dname)))
	{
		while ((dc = readdir(d)))
		{
			if ((!(flags & 0) && !(flags & 0b100)) && dc->d_name[0] == '.')
				continue;
			rd[i] = ft_new_rec(dc, dc->d_name, path);
			++i;
		}
		closedir(d);
	}
	else if ((rd[i] = ft_new_rec(NULL, dname, path)))
		return (ft_printdir(rd, flags));
	else
		ft_printf("ft_ls: %s: No such file or directory\n", dname);
	rd[i] = NULL;
	if (!(flags & 0b100))
		ft_dir_sort(rd, flags);
	if (flags & 0b100 || flags & 0b100000)
		ft_print_total_blocks(rd);
	ft_printdir(rd, flags);
	i = 0;
	if (flags & 0b10000000)
		while (rd[i])
		{
			if (rd[i]->de->d_type == 4 && !((rd[i]->de->d_name[0] == '.' && rd[i]->de->d_namlen == 1) || (ft_strequ(rd[i]->de->d_name, "..") && rd[i]->de->d_namlen == 2)))
			{
				ft_printf("\n%s:\n", rd[i]->path);
				if (flags & 0b100 || flags & 0b100000)
					ft_print_total_blocks(rd);
				ft_readdir((rd[i]->path), flags);
				// ft_printf("\n");
			}
			++i;
		}

	// di = 0;
	// dn = NULL;
	// while (rd[di])
	// {
	// 	ft_printf("\n%s/%s:\n", dname, (rd[di])->d_name);
	// 	dn = ft_strnew(ft_strlen(dname) + ft_strlen((rd[di])->d_name) + 1);
	// 	ft_strcpy(dn, dname);
	// 	dn[ft_strlen(dname)] = '/';
	// 	ft_strcpy(dn + ft_strlen(dname) + 1, (rd[di])->d_name);
	// 	ft_printdir(dn, flags);
	// 	ft_strdel(&dn);
	// 	free(rd[di]);
	// 	rd[di] = NULL;
	// 	++di;
	// }
}

void	ft_ls(char **p, uint32_t f)
{
	t_us	i;
	t_rec	*r[500];

	i = 0;
	if (!p[0])
	{
		r[0] = ft_new_rec(NULL, ".", "");
		++i;
	}
	else
		while (p[i])
		{
			r[i] = ft_new_rec(NULL, p[i], "");
			++i;
		}
	r[i] = NULL;
	ft_sort(r, f, i);
	if (f)
		return ;
	else
		return ;
}

int		main(int ac, char **av)
{
	t_us	i;
	// t_us	flags[FLAGS_COUNT];
	uint32_t	flags;
	char	*params[ac - 1];

	// ft_memset(flags, 0, FLAGS_COUNT);
	i = ac;
	flags = ft_get_flags(++av, &ac);
	ft_get_params(params, (av + (i - ac - 1)), ac);
	ft_ls(params, flags);
	return (0);
}
