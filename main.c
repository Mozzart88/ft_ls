/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 22:30:02 by tvanessa          #+#    #+#             */
/*   Updated: 2020/02/07 20:07:08 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define LETER_FLAGS "adfgGlrRtu"
#define FLAGS_COUNT 10
#define WORD_FLAGS {}
#define STRICT_FLAGS_ORDER 1
typedef struct stat	t_stat;
typedef struct timespec	t_time;
typedef struct passwd	t_pwd;
typedef struct group	t_grp;
typedef	struct		s_rec
{
	t_de			*de;
	t_stat			*st;
	struct s_rec	*conten[512];
	void			(*sort)(struct s_rec*, char[10]);
	void			(*print)(struct s_rec*, char[10]);
	char			path[__DARWIN_MAXPATHLEN];
}					t_rec;
typedef struct		s_datetime
{
	long	sec;
	long	min;
	long	hour;
	long	day;
	long	mon;
	long	year;
	char	*monstr[12];
}					t_datetime;

void	ft_get_flags(t_us *arr, char **av, int *len)
{
	char	*ai;

	while (--*len)
	{
		if (*av[0] != '-' && STRICT_FLAGS_ORDER)
			break;
		++*av;
		while (**av)
		{
			if ((ai = ft_strchr(LETER_FLAGS, **av)))
				arr[ai - LETER_FLAGS] = **av;
			else
			{
				ft_printf("Undefined flag %c passed!\n", **av);
				exit (-1);
			}
			++*av;
		}
		++av;
	}
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

t_rec	*ft_new_rec(t_de *de, char *name, char path[__DARWIN_MAXPATHLEN])
{
	t_rec	*r;

	r = NULL;
	if (!(r = (t_rec*)malloc(sizeof(t_rec))))
		return (NULL);
	ft_memset(r->path, 0, __DARWIN_MAXPATHLEN);
	ft_strcat(r->path, path);
	ft_strcat(r->path, name);
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
		return (NULL);
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

void	ft_printdir(t_rec **rd, t_us *f)
{
	t_us	i;

	i = 0;
	if (!*rd)
	 return ;
	if (f[5])
	{
		ft_print_stat((*rd)->st->st_mode);
		ft_printf("%5 hu", (*rd)->st->st_nlink);
		if (!f[3])
			ft_print_user((*rd)->st->st_uid);
		ft_print_group((*rd)->st->st_gid);
		ft_printf("%7 lld", (*rd)->st->st_size);
		if (f[9])
			ft_print_time((*rd)->st->st_atimespec);
		else
			ft_print_time((*rd)->st->st_mtimespec);
	}
	ft_print_filename(*rd, f[4]);
	if (*(rd + 1))
		ft_printdir(rd + 1, f);
}

void	ft_dir_sort(t_rec **d, t_us *f)
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

void	ft_readdir(char *dname, t_us *flags)
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
	if (!flags[1] && (d = opendir(dname)))
	{
		while ((dc = readdir(d)))
		{
			if ((!flags[0] && !flags[2]) && dc->d_name[0] == '.')
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
	if (!flags[2])
		ft_dir_sort(rd, flags);
	if (flags[2] || flags[5])
		ft_print_total_blocks(rd);
	ft_printdir(rd, flags);
	i = 0;
	if (flags[7])
		while (rd[i])
		{
			if (rd[i]->de->d_type == 4 && !((rd[i]->de->d_name[0] == '.' && rd[i]->de->d_namlen == 1) || (ft_strequ(rd[i]->de->d_name, "..") && rd[i]->de->d_namlen == 2)))
			{
				ft_printf("\n%s:\n", rd[i]->path);
				if (flags[2] || flags[5])
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

void	ft_ls(char **p, t_us *f)
{
	t_us	i;

	i = 0;
	if (!p[0])
		ft_readdir(".", f);
	else
	{
		while (p[i])
		{
			ft_stat(p[i], f);
			++i;
		}			
	}
	
}

int		main(int ac, char **av)
{
	t_us	i;
	t_us	flags[FLAGS_COUNT];
	char	*params[ac - 1];
	t_stat	*sts[500];

	ft_memset(flags, 0, FLAGS_COUNT);
	i = ac;
	ft_get_flags(flags, ++av, &ac);
	ft_get_params(params, (av + (i - ac - 1)), ac);
	i = 0;
	if (!params[i])
		ft_readdir(".", flags);
	else
		while (params[i])
		{
			if (!(sts[i] = (t_stat*)malloc(sizeof(t_stat))))
				return (-1);
			stat(params[i], sts[i]);
			++i;
		}
	sts[i] = NULL;
	
	// while (params[i])
	// {
	// 	if (i > 0 || params[i + 1])
	// 		ft_printf("%s:\n", params[i]);
	// 	ft_readdir(params[i], flags);
	// 	if (params[i + 1])
	// 		ft_printf("\n");
	// 	++i;
	// }
	return (0);
}
