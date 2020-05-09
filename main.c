/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 22:30:02 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/09 22:30:15 by mozzart          ###   ########.fr       */
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

t_vect	*ft_get_params(char **av, int len)
{
	int		i;
	t_vect *v;

	i = 0;
	if (!(v = ft_new_vect(NULL, sizeof(char*), len)))
		return (NULL);
	while (len--)
	{
		if (*av[0] == '-' && STRICT_FLAGS_ORDER)
		{
			ft_destroy_vect(v);
			break;
		}
		v->arr[i] = *(t_ull*)av;
		++av;
		++i;	
	}
	// arr[i] = NULL;
	return (v);
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
	// if (!id)
	// 	return ;
	if (!(p = getpwuid(id)))
		return ;
	ft_printf("%9s", p->pw_name);
	// free(p);
}

void	ft_print_group(gid_t id)
{
	t_grp *g;
	// if (!id)
	// 	return ;
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
	ft_printf(" %3 s %2 s %2 s:%2 s", rd[1], rd[2], rt[0], rt[1]);
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
/*
**	Print record info according to flags
*/
void	ft_print_rifo(t_rec *rd, uint32_t f)
{
	t_us	i;

	i = 0;
	if (f & L_FLAG) // 0b100000
	{
		ft_print_stat(rd->st->st_mode);
		if (rd->xattrs > 0)
			ft_printf("@");
		ft_printf("%4 hu", rd->st->st_nlink);
		if (!(f & G_FLAG)) // 0b1000
			ft_print_user(rd->st->st_uid);
		ft_print_group(rd->st->st_gid);
		ft_printf("%7 lld", rd->st->st_size);
		if (f & U_FLAG) // 0b1000000000
			ft_print_time(rd->st->st_atimespec);
		else
			ft_print_time(rd->st->st_mtimespec);
	}
	ft_print_filename(rd, f & UG_FLAG); // 0b10000
}

void	ft_print_total_blocks(t_vect *rd)
{
	blkcnt_t	bc;
	size_t		i;

	bc = 0;
	i = 0;
	while (rd->len > i)
	{
		bc += ((t_rec*)rd->arr[i])->st->st_blocks;
		++i;
	}
	ft_printf("total %lld\n", bc);
}

int	ft_readdir(char *dname, uint32_t flags, t_us size)
{
	DIR		*d;
	t_de	*dc;
	t_vect	*rd;
	t_us	i;
	char	path[__DARWIN_MAXPATHLEN];

	i = 0;
	ft_memset(path, 0, __DARWIN_MAXPATHLEN);
	ft_strcpy(path, dname);
	ft_strcat(path, "/");
	if (!(rd = ft_new_vect(NULL, sizeof(t_rec), size)))
		return (-1);
	if ((d = opendir(dname)))
	{
		while ((dc = readdir(d)))
		{
			rd->arr[i] = (t_ull)ft_new_rec(dc, dc->d_name, path);
			++i;
		}
		closedir(d);
	}
	else
		return (errno);
	if (flags & F_FLAG || flags & L_FLAG) // 0b100 0b100000
		ft_print_total_blocks(rd);
	ft_print_recs(rd, flags, 0x4);
	if (flags & UR_FLAG)
		ft_print_recs(rd, flags, 0x2);
	return (0);
}

/*
**	@d -	0x1 print only files
**			0x2 print onli dirs
**			0x4 print all
**			0x8 print print '.' content
*/
void	ft_print_recs(t_vect *r, uint32_t f, t_us d)
{
	size_t	i;
	char	name[__DARWIN_MAXPATHLEN];
	t_us	p;
	int		e;

	i = 0;
	ft_sort_recs(r, f);
	while (i < r->len)
	{
		p = 0;
		p = ft_strequ(((t_rec*)(r->arr[i]))->name, ".") ? 1 : ft_strequ(((t_rec*)(r->arr[i]))->name, "..");
		if ((d == 0x2 || d == 0x8) && (((t_rec*)(r->arr[i]))->st->st_mode & S_IFMT) == S_IFDIR)
		{
			if (!(f & D_FLAG) && (!p || d == 0x8))
			{
				ft_get_path((t_rec*)r->arr[i], name);
				if (r->len > 1)
					ft_printf("\n%s:\n", name);
				if (f & UR_FLAG)
					e = ft_readdir(name, f, ((t_rec*)r->arr[i])->st->st_nlink);
				else
					e = ft_readdir(name, f | D_FLAG, ((t_rec*)r->arr[i])->st->st_nlink);
				if (e)
					ft_dprintf(2, "ft_ls: %s: %s\n", ((t_rec*)(r->arr[i]))->name, strerror(e));
			}
			else if (d == 0x8)
				ft_print_rifo((t_rec*)r->arr[i], f);
		}
		else if ((d == 0x1 && (((t_rec*)(r->arr[i]))->st->st_mode & S_IFMT) != S_IFDIR) || d == 0x4)
			ft_print_rifo((t_rec*)r->arr[i], f);
		++i;
	}
}

void	ft_ls(t_vect *p, uint32_t f, char *path)
{
	t_us	i;
	t_vect	*v;
	t_rec	*r;

	i = 0;
	if (f)
		;
	if (!p->len && ++p->len)
		*(char**)p->arr[0] = ".";
	if (!(v = ft_new_vect(NULL, sizeof(t_rec), p->len)))
		return ;
	while (i < v->len)
	{
		r = ft_new_rec(NULL, (char*)*(p->arr), path);
		++p->arr;
		if (r->_errno)
		{
			ft_dprintf(2, "ft_ls: %s/%s: %s\n", r->path, r->name, r->_errstr);
			// r[i]->destroy(r[i]);
			--v->len;
			continue;
		}
		v->arr[i] = (t_ull)r;
		++i;
	}
	if (f & D_FLAG)
		ft_print_recs(v, f, 0x4);
	else
	{
		ft_print_recs(v, f, 0x1);
		ft_print_recs(v, f, 0x8);
	}
	return;
}

static int ft_strcmp_s(t_ull a, t_ull b)
{
	return (ft_strcmp((char*)a, (char*)b));
}

int		main(int ac, char **av)
{
	t_us	i;
	uint32_t	flags;
	t_vect	*params;

	i = ac;
	flags = ft_get_flags(++av, &ac);
	params = ft_get_params((av + (i - ac - 1)), ac);

	ft_msort(params, 1, ft_strcmp_s);
	ft_ls(params, flags, "");
	return (0);
}
