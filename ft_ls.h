/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 17:32:28 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/15 00:14:04 by mozzart          ###   ########.fr       */
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

#define LETER_FLAGS "adfgGlrRtu1"
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
/*
**	Long format flags mask: -lg
*/ 
#define LF_FLAGS	0x28
/*
**	All entries flags mask: -af
*/ 
#define AE_FLAGS	0x5
#define FLAGS_COUNT 11
#define WORD_FLAGS {}
#define STRICT_FLAGS_ORDER 1

typedef struct stat	t_stat;
typedef struct timespec	t_time;
typedef struct passwd	t_pwd;
typedef struct group	t_grp;
typedef struct dirent t_de;
typedef	struct		s_rec
{
	t_stat			*st;
	char			path[__DARWIN_MAXPATHLEN];
	char			name[__DARWIN_MAXNAMLEN];
    int             _errno;
    char*           _errstr;
    char			xattrs[__DARWIN_MAXPATHLEN];
    char			lnk_path[__DARWIN_MAXPATHLEN];
    struct s_rec	*lnk_to;
}					t_rec;
typedef struct		s_datetime
{
	long	sec;
	long	min;
	long	hour;
	long	mday;
	long	mon;
	long	year;
	long	wday;
	long	yday;
	char	*daystr;
	char	*monstr;
}					t_datetime;
typedef struct		s_vect
{
	t_ull	*arr;
	size_t	size;
	size_t	len;
	size_t	ilen;
	t_us	is_sorted;
	void	(*arr_destroier)(void**);
}					t_vect;
typedef struct		s_maxvallen
{
	t_ull	lnk;
	t_ull	un;
	t_ull	gn;
	t_ull	sl;
	t_ull	maj;
	t_ull	min;
}					t_maxvallen;

t_rec*   ft_new_rec(char* name, char path[MAXNAMLEN]);
int		ft_msort(t_vect *v, t_us asc, long long f(t_ull, t_ull));
void    ft_sort_recs(t_vect *arr, uint32_t flags);
void	ft_ls(t_vect *p, uint32_t f);
// void	ft_print_recs(t_vect *r, uint32_t f, t_us d);
void	ft_print_all(t_vect *r, uint32_t *f);
void	ft_print_files(t_vect *r, uint32_t *f);
void	ft_print_dirs(t_vect *r, uint32_t *f);
char	*ft_get_path(t_rec *r, char *dst);
char	*ft_get_lnk_path(t_rec *r, char *dst);
t_vect	*ft_new_vect(void *a, size_t s, size_t l, void arr_destroier(void**));
void	*ft_destroy_vect(t_vect **v);
void	ft_destroy_rec(void **record);

#endif
