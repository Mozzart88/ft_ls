/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 17:32:28 by tvanessa          #+#    #+#             */
/*   Updated: 2020/04/23 01:14:25 by mozzart          ###   ########.fr       */
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
    int             _errno;
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
void	ft_msort(void *arr[], t_us size);
void    ft_sort(t_rec **arr, uint32_t flags, t_us arr_len);

#endif
