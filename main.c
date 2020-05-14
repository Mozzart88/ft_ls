/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 22:30:02 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/15 02:36:12 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

uint32_t	ft_get_flags(char ***av, int *len)
{
	char		*ai;
	uint32_t	r;
	uint32_t	b;

	r = 0;
	// if (ft_strequ(**av, "--"))
	// {
	// 	--*len;
	// 	++*av;
	// 	return (r);
	// }
	while (*len)
	{
		if (ft_strequ(**av, "--"))
		{
			--*len;
			++*av;
			return (r);
		}
		if (**av[0] != '-' && STRICT_FLAGS_ORDER)
			break;
		if (ft_strlen(**av) <= 1)
			break;
		++**av;
		while (***av)
		{
			if ((ai = ft_strchr(LETER_FLAGS, ***av)))
			{
				b = (1 << (ai - LETER_FLAGS));
				if (b & 0x420 && r & 0x420)
					r ^= (r & 0x420);
				if (b & 0x408 && r & 0x408)
					r ^= (r & 0x408);
				r |= b;
			}
				// arr[ai - LETER_FLAGS] = ***av;
			else
			{
				ft_dprintf(2, "/bin/ls: illegal option -- %c\n", ***av);
				ft_dprintf(2, "usage: ls [-@ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1%] [file ...]\n", ***av);
				exit (1);
			}
			++**av;
			// r <<= 1;
		}
		++*av;
		--*len;
	}
	return (r);
}
void	ft_strdelv(void **addr)
{
	char	**str;

	str = (char**)addr;
	ft_strdel(str);
}


t_vect	*ft_get_params(char **av, int len)
{
	int		i;
	t_vect *v;

	i = 0;
	if (!len)
	{
		++len;
		av[0] = ".";
	}
	if (!(v = ft_new_vect(NULL, sizeof(char*), len, NULL)))
		return (NULL);
	while (len--)
	{
		// printf("%s\n", av[i]);
		// if (*av[0] == '-' && STRICT_FLAGS_ORDER)
		// {
		// 	ft_destroy_vect(&v);
		// 	break;
		// }
		v->arr[i] = *(t_ull*)av;
		++av;
		++i;	
	}
	// arr[i] = NULL;
	return (v);
}

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
	// if (r == S_IFREG)
	// 	return ('-');
	if (r == S_IFLNK)
		return ('l');
	if (r == S_IFSOCK)
		return ('s');
	return ('-');
}

void	ft_print_stat(t_rec *r)
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
			m[i] =  r->st->st_mode & j ? m[i] : ft_toupper(m[i]);
		}
		else
			m[i] = r->st->st_mode & j ? t[i - 1] : '-';
		mask = i % 3 == 0 ? mask >> 1 : mask;
	}
	m[10] = r->xattrs[0] ? '@' : '\0';
	m[11] = '\0';
	ft_printf("%-11s ", m);
}

void	ft_print_user(uid_t id)
{
	t_pwd *p;
	if (!(p = getpwuid(id)))
		return ;
	ft_printf("%9s", p->pw_name);
}

char	*ft_get_user_name(uid_t id)
{
	t_pwd *p;
	char	*name;
	char	buff[_SC_GETPW_R_SIZE_MAX];

	if (!(p = (t_pwd*)malloc(sizeof(t_pwd))))
		return (NULL);
	if ((getpwuid_r(id, p, buff, _SC_GETPW_R_SIZE_MAX, &p)) || !p)
		name = ft_itoa_long_un(id);
	else
		name = ft_strdup(p->pw_name);
	p->pw_name = NULL;
	p->pw_passwd = NULL;
	p->pw_class = NULL;
	p->pw_gecos = NULL;
	p->pw_dir = NULL;
	p->pw_shell = NULL;
	p->pw_change = 0;
	p->pw_expire = 0;
	p->pw_uid = 0;
	p->pw_gid = 0;
	free(p);
	p = NULL;
	return (name);
}

void	ft_print_group(gid_t id)
{
	t_grp *g;
	if (!(g = getgrgid(id)))
		return ;
	ft_printf("%6s", g->gr_name);
}

char	*ft_get_group_name(gid_t id)
{
	t_grp *g;
	char	*name;
	char	buff[_SC_GETGR_R_SIZE_MAX * MAXLOGNAME];

	if (!(g = (t_grp*)malloc(sizeof(t_grp))))
		return (NULL);
	if ((getgrgid_r(id, g, buff, _SC_GETGR_R_SIZE_MAX * MAXLOGNAME, &g)) || !g)
		name = ft_itoa_long_un(id);
	else
		name = ft_strdup(g->gr_name);
	g->gr_mem = NULL;
	g->gr_passwd = NULL;
	g->gr_name = NULL;
	g->gr_gid = 0;
	free(g);
	g = NULL;
	return (name);
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

/* t_datetime	*ft_new_dt()
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
 */
/* t_datetime	*ft_ctime(const time_t *t)
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
 */
/* static void	ft_swap(t_ull *a, t_ull *b)
{
	t_ull	t;

	t = *a;
	*a = *b;
	*b = t;
	return;
}
 */
void		ft_set_loc(t_datetime *dt)
{
	char 	*mon[12];
	int	i;

	mon[0] = "Jan янв";
	mon[1] = "Feb фев";
	mon[2] = "Mar мар";
	mon[3] = "Apr апр";
	mon[4] = "May май";
	mon[5] = "Jun июн";
	mon[6] = "Jul июл";
	mon[7] = "Aug авг";
	mon[8] = "Sep сен";
	mon[9] = "Oct окт";
	mon[10] = "Nov ноя";
	mon[11] = "Dec дек";
	i = -1;
	while (++i < 12)
		if ((ft_strstr(mon[i], dt->monstr)))
			dt->monstr = (mon[i] + 4);
}

t_datetime	ft_localtime(t_time *t)
{
	t_datetime	dt;
	char		*ct;

	ct = ctime(&t->tv_sec);
	dt.daystr = ft_strsub(ct, 0, 3);
	dt.monstr = ft_strsub(ct, 4, 3);
	dt.mday = ft_atoi(ft_strsub(ct, 8, 2));
	dt.hour = ft_atoi(ft_strsub(ct, 11, 2));
	dt.min = ft_atoi(ft_strsub(ct, 14, 2));
	dt.sec = ft_atoi(ft_strsub(ct, 17, 2));
	dt.year = ft_atoi(ft_strsub(ct, 20, 4));
	if (ft_strequ(getenv("LANG"), "ru_RU.UTF-8"))
		ft_set_loc(&dt);
	return (dt);
}

time_t	ft_difftime(time_t *t1, time_t *t2)
{
	return (*t1 - *t2);
}

void	ft_print_time(t_time t)
{
	time_t	tl;
	t_datetime dt;
	long long	dif_time;

	tl = time(NULL);
	dt = ft_localtime(&t);
	dif_time = ft_difftime(&tl, &t.tv_sec);
/* 	
	if (dif_time < (31536000L / 2) && dif_time > (31536000L / 2 * -1))
	{
		if (ft_strequ(getenv("LANG"), "ru_RU.UTF-8"))
			ft_printf("%2d %6s %02d:%02d ", dt.mday, dt.monstr, dt.hour, dt.min);
		else
			ft_printf("%3s %2d %02d:%02d ", dt.monstr, dt.mday, dt.hour, dt.min);
	}
	else if (ft_strequ(getenv("LANG"), "ru_RU.UTF-8"))
		ft_printf("%2d %6s %-5 d ", dt.mday, dt.monstr, dt.year);
	else
		ft_printf("%3s %2d %-5 d ", dt.monstr, dt.mday, dt.year);
*/
	if (ft_strequ(getenv("LANG"), "ru_RU.UTF-8"))
	{
		if (dif_time < (31536000L / 2) && dif_time >= 0)
			ft_printf("%2d %6s %02d:%02d ", dt.mday, dt.monstr, dt.hour, dt.min);
		else
			ft_printf("%2d %6s %-5 d ", dt.mday, dt.monstr, dt.year);
	}
	else
	{
		if (dif_time < (31536000L / 2) && dif_time > (31536000L / 2 * -1))
			ft_printf("%3s %2d %02d:%02d ", dt.monstr, dt.mday, dt.hour, dt.min);
		else
			ft_printf("%3s %2d %-5 d ", dt.monstr, dt.mday, dt.year);
	}
}

void	ft_print_filename(t_rec *r, t_us f)
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
/*
**	Print record info according to flags
*/
void	ft_print_rifo(t_rec *rd, uint32_t *f, t_maxvallen mvl)
{
	t_us	i;

	i = 0;
	if (*f & LF_FLAGS)
	{
		ft_print_stat(rd);
		
		ft_printf("%* hu ", mvl.lnk, rd->st->st_nlink);
		if (!(*f & G_FLAG)) // 0b1000
			ft_printf("%-*s ", mvl.un + 1, ft_get_user_name(rd->st->st_uid));
		ft_printf("%-*s ", mvl.gn + 1, ft_get_group_name(rd->st->st_gid));
		if ((rd->st->st_mode & S_IFMT) == S_IFCHR || (rd->st->st_mode & S_IFMT) == S_IFBLK)
		{
			ft_printf(" %*lld", mvl.maj, (rd->st->st_rdev >> 24) & 0377);
			ft_printf(", %*lld ", mvl.min < 3 ? 3 : mvl.min, rd->st->st_rdev & 0377);
		}
		else
			ft_printf("%*lld ", mvl.sl < mvl.maj + mvl.min ? mvl.maj + mvl.min + 3 : mvl.sl, rd->st->st_size);
		if (*f & U_FLAG) // 0b1000000000
			ft_print_time(rd->st->st_atimespec);
		else
			ft_print_time(rd->st->st_mtimespec);
	}
	ft_print_filename(rd, *f); // 0b10000
	*f &= 0xFFF;
}

void	ft_print_total_blocks(t_vect *rd, uint32_t f)
{
	blkcnt_t	bc;
	size_t		i;
	t_rec		*r;

	bc = 0;
	i = 0;
	while (rd->len > i)
	{
		r = (t_rec*)rd->arr[i];
		if (!(f & AE_FLAGS) && r->name[0] == '.' && ++i)
			continue;
		bc += r->st->st_blocks;
		++i;
	}
	ft_printf("total %lld\n", bc);
}

int	ft_readdir(char *dname, uint32_t flags)
{
	DIR		*d;
	t_de	*dc;
	t_vect	*rd;
	t_us	i;
	char	path[__DARWIN_MAXPATHLEN];
	t_rec	*des[LINK_MAX];

	i = 0;
	ft_memset(path, 0, __DARWIN_MAXPATHLEN);
	ft_strcpy(path, dname);
	ft_strcat(path, "/");
	if ((d = opendir(dname)))
	{
		while ((dc = readdir(d)))
		{
			des[i] = ft_new_rec(dc->d_name, path);
			++i;
		}
		closedir(d);
	}
	else
		return (errno);
	if (!(rd = ft_new_vect(NULL, sizeof(t_rec), i, ft_destroy_rec)))
		return (-1);
	i = 0;
	while (i < rd->len)
	{
		rd->arr[i] = (t_ull)des[i];
		++i;
	}
	if (flags & LF_FLAGS && (rd->len > 2 || flags & AE_FLAGS))
		ft_print_total_blocks(rd, flags);
	ft_print_all(rd, &flags);
	if (flags & UR_FLAG)
		ft_print_dirs(rd, &flags);
	ft_destroy_vect(&rd);
	return (0);
}
t_us		ft_is_dir(mode_t m)
{
	if ((m & S_IFMT) == S_IFDIR)
		return (1);
	return (0);
}
t_us		ft_is_spec(mode_t m)
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
t_us		ft_is_lnk(mode_t m)
{
	if ((m & S_IFMT) == S_IFLNK)
		return (1);
	return (0);
}
t_us		ft_is_reg_file(mode_t m)
{
	if ((m & S_IFMT) == S_IFREG)
		return (1);
	return (0);
}
t_maxvallen	ft_new_mvl(t_vect *v, uint32_t f)
{
	size_t		i;
	t_maxvallen mvl;
	t_maxvallen cvl;
	t_rec		*r;
	char		*names[2];

	mvl.gn = 0;
	mvl.un = 0;
	mvl.lnk = 0;
	mvl.sl = 0;
	mvl.maj = 0;
	mvl.min = 0;
	i = 0;
	while (i < v->len)
	{
		r = (t_rec*)v->arr[i];
		if (r->name[0] != '.' || (f & AE_FLAGS) || (f & 0x1000))
		{
			cvl.lnk = ft_count_digits(r->st->st_nlink);
			cvl.sl = ft_count_digits(r->st->st_size);
			cvl.maj = ft_count_digits((r->st->st_rdev >> 24) & 0377);
			cvl.min = ft_count_digits(r->st->st_rdev & 0377);
			names[0] = ft_get_group_name(r->st->st_gid);
			names[1] = ft_get_user_name(r->st->st_uid);
			cvl.gn = ft_strlen(names[0]);
			cvl.un = ft_strlen(names[1]);
			if (cvl.lnk > mvl.lnk)
				mvl.lnk = cvl.lnk;
			if (cvl.sl > mvl.sl)
				mvl.sl = cvl.sl;
			if (cvl.gn > mvl.gn)
				mvl.gn = cvl.gn;
			if (cvl.un > mvl.un)
				mvl.un = cvl.un;
			if (ft_is_spec(r->st->st_mode))
			{
				if (cvl.maj > mvl.maj)
					mvl.maj = cvl.maj;
				if (cvl.min > mvl.min)
					mvl.min = cvl.min;
			}
			ft_strdel(&(names[0]));
			ft_strdel(&(names[1]));
		}
		++i;
	}
	return (mvl);
}
/* 
** if -d flag and many args
** or if passed one arg as dir and nor recursive
** or if in recursive and print content
*/
void 	ft_print_all(t_vect *r, uint32_t *f)
{
	size_t		i;
	// char		name[__DARWIN_MAXPATHLEN];
	t_us		p;
	// int			e;
	t_maxvallen	mvl;

	i = 0;
	ft_sort_recs(r, *f);
	mvl = ft_new_mvl(r, *f);
	while (i < r->len)
	{
		p = ((t_rec*)(r->arr[i]))->name[0] == '.' ? 1 : 0;
		if (*f & 0x800 && !(*f ^= 0x800))
			p = 0;
		if (!p || *f & AE_FLAGS || *f & 0x1000)
			ft_print_rifo((t_rec*)r->arr[i], f, mvl);
		++i;
	}
}
/* 
** if passed many args and no -d flag
*/
void 	ft_print_files(t_vect *r, uint32_t *f)
{
	size_t		i;
	t_us		p;
	t_rec		*rec;
	t_maxvallen	mvl;

	i = 0;
	ft_sort_recs(r, *f);
	mvl = ft_new_mvl(r, *f);
	while (i < r->len)
	{
		rec = ((t_rec*)(r->arr[i]));
		p = ((t_rec*)(r->arr[i]))->name[0] == '.' ? 1 : 0;
		if (*f & 0x800)
			p = 0;
		if (!p || *f & AE_FLAGS)
		{
			if (!(ft_is_dir(rec->st->st_mode)) && (!(ft_is_lnk(rec->st->st_mode)) || *f & LF_FLAGS))
				ft_print_rifo((t_rec*)r->arr[i], f, mvl);
			else if (ft_is_lnk(rec->st->st_mode) && !(ft_is_dir(rec->lnk_to->st->st_mode)))
				ft_print_rifo((t_rec*)r->arr[i], f, mvl);
		}
		++i;
	}
}
/*
** if passed many args whith dirs
** and flag -d not present 
** or -R flag present
*/
void 	ft_print_dirs(t_vect *r, uint32_t *f)
{
	size_t		i;
	char		name[__DARWIN_MAXPATHLEN];
	t_us		p;
	int			e;
	t_maxvallen	mvl;

	i = 0;
	ft_sort_recs(r, *f);
	mvl = ft_new_mvl(r, *f);
	while (i < r->len)
	{
		if (AE_FLAGS & *f)
			p = ft_strequ(((t_rec*)r->arr[i])->name, ".") ? 1 : ft_strequ(((t_rec*)r->arr[i])->name, "..");
		else
			p = ((t_rec*)(r->arr[i]))->name[0] == '.' ? 1 : 0;
		if ((*f & 0x800))
			p = 0;
		if (ft_is_dir(((t_rec*)(r->arr[i]))->st->st_mode))
		{
			if (!(*f & D_FLAG) && (!p))
			{
				ft_get_path((t_rec*)r->arr[i], name);
				if (*f & 0x1000 && r->ilen > 1)
					ft_printf("%s:\n", name);
				else if (r->ilen > 1)
					ft_printf("\n%s:\n", name);
				if ((e = ft_readdir(name, *f & UR_FLAG ? *f & 0x7FF : (*f & 0x7FF) | D_FLAG)))
					ft_dprintf(2, "ft_ls: %s: %s\n", ((t_rec*)(r->arr[i]))->name, strerror(e));
			}
		}
		else if (ft_is_lnk(((t_rec*)(r->arr[i]))->st->st_mode) && ft_is_dir(((t_rec*)(r->arr[i]))->lnk_to->st->st_mode) && !(*f & LF_FLAGS))
		{
			if (!(*f & D_FLAG) && (!p))
			{
				ft_get_path(((t_rec*)r->arr[i]), name);
				if (*f & 0x1000 && r->len > 1)
					ft_printf("%s:\n", name);
				else if (r->len > 1)
					ft_printf("\n%s:\n", name);
				// ft_get_path(((t_rec*)r->arr[i])->lnk_to, name);
				if ((e = ft_readdir(name, *f & UR_FLAG ? *f & 0x7FF : (*f & 0x7FF) | D_FLAG)))
					ft_dprintf(2, "ft_ls: %s: %s\n", ((t_rec*)(r->arr[i]))->lnk_to->name, strerror(e));
			}
		}
		*f &= 0xFFF;
		++i;
	}
}

/*
**	@d -	0x1 print only files
**			0x2 print onli dirs
**			0x4 print all
**			0x8 print print '.' content
*/
/* 
void	ft_print_recs(t_vect *r, uint32_t f, t_us d)
{
	size_t		i;
	char		name[__DARWIN_MAXPATHLEN];
	t_us		p;
	int			e;
	t_maxvallen	mvl;

	i = 0;
	ft_sort_recs(r, f);
	mvl = ft_new_mvl(r, f);
	while (i < r->len)
	{
		// p = ((t_rec*)(r->arr[i]))->name[0] == '.' ? 1 : 0;
		p = ft_strequ(((t_rec*)r->arr[i])->name, ".") ? 1 : ft_strequ(((t_rec*)r->arr[i])->name, "..");
		if (p && !(f & AE_FLAGS) && d != 0x8)
			;
		else if ((d & 0xA) && (((t_rec*)(r->arr[i]))->st->st_mode & S_IFMT) == S_IFDIR)
		{
			if (!(f & D_FLAG) && (!p || d & 0x8))
			{
				ft_get_path((t_rec*)r->arr[i], name);
				if (r->len > 1)
					ft_printf("\n%s:\n", name);
				if (f & UR_FLAG)
					e = ft_readdir(name, f);
				else
					e = ft_readdir(name, f | D_FLAG);
				if (e)
					ft_dprintf(2, "ft_ls: %s: %s\n", ((t_rec*)(r->arr[i]))->name, strerror(e));
			}
			else if (d == 0x8)
				ft_print_rifo((t_rec*)r->arr[i], f, mvl);
		}
		else if ((d == 0x1 && (((t_rec*)(r->arr[i]))->st->st_mode & S_IFMT) != S_IFDIR && (!p || f & AE_FLAGS)) || d == 0x4)
			ft_print_rifo((t_rec*)r->arr[i], f, mvl);
		++i;
	}
}
 */
void	ft_ls(t_vect *p, uint32_t f)
{
	t_us	i;
	t_vect	*v;
	t_rec	*r;

	i = 0;
	if (f)
		;
	// if (!p->len && ++p->len)
	// 	*(char**)p->arr[0] = ".";
	if (!(v = ft_new_vect(NULL, sizeof(t_rec), p->len, ft_destroy_rec)))
		return ;
	while (i < v->len)
	{
		r = ft_new_rec((char*)*(p->arr), "");
		++p->arr;
		if (r->_errno)
		{
			ft_dprintf(2, "ls: %s: %s\n", (char*)*(p->arr - 1), r->_errstr);
			// r[i]->destroy(r[i]);
			// ft_destroy_vect(&v);
			ft_destroy_rec((void**)&r);
			--v->len;
			continue;
		}
		v->arr[i] = (t_ull)r;
		++i;
	}
	f |= 0x1800;
	if (f & D_FLAG)
		ft_print_all(v, &f);
	else
	{
		ft_print_files(v, &f);
		ft_print_dirs(v, &f);
	}
	// p->arr = p->arr - i;
	p->arr = p->arr - p->len;
	p->len = i;
	ft_destroy_vect(&v);
	return;
}

static long long ft_strcmp_s(t_ull a, t_ull b)
{
	return (ft_strcmp((char*)a, (char*)b));
}
int		main(int ac, char **av)
{
	t_us	i;
	uint32_t	flags;
	t_vect	*params;

	// char	*dd = "--";
	// ac = 2;
	// av[1] = dd;
	// setlocale(0, "");
	// ft_printf("%s\n", getenv("LANG"));
	// ft_printf("%s\n", setlocale(LC_ALL, ""));
	// ft_printf("%d\n", ac);
	// exit (0);
	i = ac;
	++av;
	--ac;
	flags = ft_get_flags(&(av), &ac);
	params = ft_get_params((av/*  + (i - ac - 1) */), ac);
	

	if (!(flags & F_FLAG))
		ft_msort(params, 0, ft_strcmp_s);
	ft_ls(params, flags);
	ft_destroy_vect(&params);
	return (0);
}
