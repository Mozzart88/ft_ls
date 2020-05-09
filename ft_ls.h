/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 17:32:28 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/09 03:01:26 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <grp.h>
# include <pwd.h>
# include <dirent.h>
# include <time.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <sys/stat.h>
# include <sys/types.h>
#include  <errno.h>

#define LETER_FLAGS "adfgGlrRtu"
/*
**	Include directory entries whose names begin with a dot (.).
*/ 
#define A_FLAG		0x1
/*
**	Directories are listed as plain files (not searched recursively).
*/ 
#define D_FLAG		0x2
/*
**	Output is not sorted.
**	This option turns on the -a option.
*/ 
#define F_FLAG		0x4
/*
**	This option is only available for compatibility with POSIX;
**	it is used to display the group name in the long (-l)
**	format output (the owner name is suppressed).
*/ 
#define G_FLAG		0x8
/*
**	Enable colorized output.
**	This option is equivalent to defining `CLICOLOR` in the environment.
*/ 
#define UG_FLAG		0x10
/*
**	(The lowercase letter "ell".) List in long format.
**	If the output is to a terminal, a total sum for all the file
**	sizes is output on a line before the long listing.
*/ 
#define L_FLAG		0x20
/*
**	Reverse the order of the sort to get reverse lexicographical order or the
**	oldest entries first (or largest files last, if combined with sort by size
*/ 
#define R_FLAG		0x40
/*
**	Recursively list subdirectories encountered.
*/ 
#define UR_FLAG		0x80
/*
**	Sort by time modified (most recently modified first) before sorting the
**	operands by lexicographical order.
*/ 
#define T_FLAG		0x100
/*
**	Use time of last access, instead of last modification of the file for
**	sorting (-t) or long printing (-l).
*/ 
#define U_FLAG		0x200
/*
**	Sorting flags mask: -frtu
*/ 
#define SORT_FLAGS	0x344
#define FLAGS_COUNT 10
#define WORD_FLAGS {}
#define STRICT_FLAGS_ORDER 1

typedef struct stat	t_stat;
typedef struct timespec	t_time;
typedef struct passwd	t_pwd;
typedef struct group	t_grp;
typedef struct dirent t_de;
typedef	struct		s_rec
{
	t_de			*de;
	t_stat			*st;
	struct s_rec	*conten[512];
	void			(*sort)(struct s_rec*, char[10]);
	void			(*print)(struct s_rec*, char[10]);
	char			path[__DARWIN_MAXPATHLEN];
	char			name[__DARWIN_MAXNAMLEN];
    int             _errno;
	int				content_size;
    char*           _errstr;
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

t_rec*   ft_new_rec(t_de* de, char* name, char path[MAXNAMLEN]);
t_de	*ft_copyde(t_de *de);
void	ft_msort(void *arr[], t_us size, t_us asc);
void    ft_sort_recs(t_rec **arr, uint32_t flags, t_us arr_len);
void	ft_ls(char **p, size_t s, uint32_t f, char *path);
void	ft_print_recs(t_rec *r[], size_t s, uint32_t f, t_us d);
char	*ft_get_path(t_rec *r, char *dst);

#endif
