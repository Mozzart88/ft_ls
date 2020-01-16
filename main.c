/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 22:30:02 by tvanessa          #+#    #+#             */
/*   Updated: 2020/01/16 15:23:40 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define LETER_FLAGS "adfgGlrRtu"
#define FLAGS_COUNT 10
#define WORD_FLAGS {}
#define STRICT_FLAGS_ORDER 1
typedef struct stat	t_stat;

void	ft_get_flags(t_us *arr, char **av, int *len)
{
	char	*ai;

	// ai = -1;
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
	// arr[++ai] = 0;
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

t_de	*ft_copydc(t_de *dc)
{
	t_de	*r;

	if (!(r = (t_de*)malloc(sizeof(t_de))))
		return (NULL);
	r->d_ino = dc->d_ino;
	ft_strcpy(r->d_name, dc->d_name);
	r->d_namlen = dc->d_namlen;
	r->d_reclen = dc->d_reclen;
	r->d_seekoff = dc->d_seekoff;
	r->d_type = dc->d_type;
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

void	ft_print_stat(t_de *de)
{
	t_stat	*st;
	int		i;
	int		j;
	char	m[11];
	char	*t;

	t = "rwxrwxrwx";
	if (!(st = (t_stat*)malloc(sizeof(t_stat))))
		return ;
	stat(de->d_name, st);
	m[0] = ft_get_file_type(st->st_mode);
	i = 1;
	j = 1 << 8;
	while (i < 10)
	{
		m[i] = st->st_mode & j ? t[i - 1] : '-';
		++i;
		j >>= 1;
	}
	m[10] = '\0';
	ft_printf("%s\t", m);
}

void	ft_printdir(char *dname, t_us *flags)
{
	DIR		*d;
	t_de	*dc;
	t_de	*rd[512];
	t_us	i;
	t_us	di;
	char	*dn;

	i = 0;
	if ((d = opendir(dname)))
	{
		while ((dc = readdir(d)))
		{
			if (!flags[0] && dc->d_name[0] == '.')
				continue;
			if (dc->d_type == 4 && flags[7] && !((dc->d_namlen == 1 && dc->d_name[0] == '.') || (dc->d_namlen == 2 && !ft_strcmp(dc->d_name, ".."))))
			{
				rd[i] = ft_copydc(dc);
				++i;
			}
			if (flags[5])
				ft_print_stat(dc);				
			ft_printf("%s -> %d\n", dc->d_name, dc->d_type);
		}
		closedir(d);
	}
	// else if (st->)
	else
		ft_printf("ft_ls: %s: No such file or directory\n", dname);
	di = 0;
	dn = NULL;
	while (di < i)
	{
		ft_printf("\n%s/%s:\n", dname, (rd[di])->d_name);
		dn = ft_strnew(ft_strlen(dname) + ft_strlen((rd[di])->d_name) + 1);
		ft_strcpy(dn, dname);
		dn[ft_strlen(dname)] = '/';
		ft_strcpy(dn + ft_strlen(dname) + 1, (rd[di])->d_name);
		ft_printdir(dn, flags);
		ft_strdel(&dn);
		free(rd[di]);
		rd[di] = NULL;
		++di;
	}
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
		ft_printdir(".", flags);
	while (params[i])
	{
		if (i > 0 || params[i + 1])
			ft_printf("%s:\n", params[i]);
		ft_printdir(params[i], flags);
		if (params[i + 1])
			ft_printf("\n");
		++i;
	}
	return (0);
}
