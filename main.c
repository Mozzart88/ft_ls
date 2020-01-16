/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 22:30:02 by tvanessa          #+#    #+#             */
/*   Updated: 2020/01/16 23:32:39 by tvanessa         ###   ########.fr       */
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
	{
		r->de = ft_copyde(de);
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
	// free(g);
}

void	ft_print_time(t_time t)
{
	char	*ct;
	char	**rt;

	ct = ctime(&t.tv_sec);
	rt = ft_strsplit(ct, ' ');
	// if (t.tv_sec)
	ft_printf(" %s %s %5s", rt[1], rt[2], rt[3]);
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
	ft_print_filename((*rd), f[4]);
	if (*(rd + 1))
		ft_printdir(rd + 1, f);
}

void	ft_dir_sort(t_rec **d, t_us *f)
{
	if (d && f)
		return ;
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
	else if (!(rd[i] = ft_new_rec(NULL, dname, path)))
		return ;
	else
		ft_printf("ft_ls: %s: No such file or directory\n", dname);
	rd[i] = NULL;
	if (!flags[2])
		ft_dir_sort(rd, flags);
	ft_printdir(rd, flags);
	i = 0;
	if (flags[7])
		while (rd[i])
		{
			if (rd[i]->de->d_type == 4 && !((rd[i]->de->d_name[0] == '.' && rd[i]->de->d_namlen == 1) || (ft_strequ(rd[i]->de->d_name, "..") && rd[i]->de->d_namlen == 2)))
			{
				ft_printf("\n%s:\n", rd[i]->path);
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

int		main(int ac, char **av)
{
	t_us	i;
	t_us	flags[FLAGS_COUNT];
	char	*params[ac - 1];

	i = 0;
	while (i < FLAGS_COUNT)
	{
		flags[i] = 0;
		++i;
	}
	// ft_memset(flags, 0, FLAGS_COUNT);
	i = ac;
	ft_get_flags(flags, ++av, &ac);
	ft_get_params(params, (av + (i - ac - 1)), ac);
	i = 0;
	if (!params[i])
		ft_readdir(".", flags);
	while (params[i])
	{
		if (i > 0 || params[i + 1])
			ft_printf("%s:\n", params[i]);
		ft_readdir(params[i], flags);
		if (params[i + 1])
			ft_printf("\n");
		++i;
	}
	return (0);
}
