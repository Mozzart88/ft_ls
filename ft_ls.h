/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 17:32:28 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/22 06:06:55 by mozzart          ###   ########.fr       */
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
// # include <sys/stat.h>
// # include <sys/types.h>
# include <errno.h>
# include <sys/acl.h>

/*
** @todo: Sort definitions
** @todo: Check for static functiomns
*/

# define LETER_FLAGS "adfgGlrRtu1SpAncUo"
# define FLAGS_COUNT 18

/*
** Include directory entries whose names begin with a dot (.).
*/
# define A_FLAG		0x1

/*
** Directories are listed as plain files (not searched recursively).
*/
# define D_FLAG		0x2

/*
** Output is not sorted.
** This option turns on the -a option.
*/
# define F_FLAG		0x4

/*
** This option is only available for compatibility with POSIX;
** it is used to display the group name in the long (-l)
** format output (the owner name is suppressed).
*/
# define G_FLAG		0x8

/*
** Enable colorized output.
** This option is equivalent to defining `CLICOLOR` in the environment.
*/
# define UG_FLAG	0x10

/*
** (The lowercase letter "ell".) List in long format.
** If the output is to a terminal, a total sum for all the file
** sizes is output on a line before the long listing.
*/
# define L_FLAG		0x20

/*
** Reverse the order of the sort to get reverse lexicographical order or the
** oldest entries first (or largest files last, if combined with sort by size
*/
# define R_FLAG		0x40

/*
** Recursively list subdirectories encountered.
*/
# define UR_FLAG	0x80

/*
** Sort by time modified (most recently modified first) before sorting the
** operands by lexicographical order.
*/
# define T_FLAG		0x100

/*
** Use time of last access, instead of last modification of the file for
** sorting (-t) or long printing (-l).
*/
# define U_FLAG		0x200

/*
** Use time of last access, instead of last modification of the file for
** sorting (-t) or long printing (-l).
*/
# define ONE_FLAG		0x400

/*
** Sort files by size.
*/
# define US_FLAG		0x800

/*
** Write a slash (‘/’) after each filename if that file is a directory.
*/
# define P_FLAG		0x1000

/*
** Write a slash (‘/’) after each filename if that file is a directory.
*/
# define UA_FLAG		0x2000

/*
** Display user and group IDs numerically, rather than converting to a
** user or group name in a long (-l) output. This option turns on the -l option.
*/
# define N_FLAG		0x4000

/*
** Use time when file status was last changed for sorting (-t) or long printing
** (-l).
*/
# define C_FLAG		0x8000

/*
** Use time of file creation, instead of last modification for sorting (-t) or
** long output (-l).
*/
# define UU_FLAG		0x10000

/*
** List in long format, but omit the group id.
*/
# define O_FLAG		0x20000

/*
** Sorting flags mask: -frtuScU
*/
# define SORT_FLAGS	0x18B44

/*
** Long format flags mask: -lgno
*/
# define LF_FLAGS	0x24028

/*
** All entries flags mask: -af
*/
# define AE_FLAGS	0x5

/*
** First zero point bit
*/
# define FT_ZP_BIT	0x1 << FLAGS_COUNT

/*
** First entry bit
*/
# define FT_F_BIT	0x1 << (FLAGS_COUNT + 1)

/*
** User defined bit mask
*/
# define FT_U_BITS	FT_F_BIT | FT_ZP_BIT

/*
** All flags mask
*/
# define FT_ALL_FLAGS	0x7FFFF

/*
** All program mask
*/
# define FT_ALL_PFLAGS	0x3FFFF

// # define WORD_FLAGS {}
# define STRICT_FLAGS_ORDER 1
# define FT_PROG_NAME "ls"
# define FT_PUSAGE "%s: illegal option -- %c\nusage: ls %s [file ...]\n"
# define FT_PUSAGE_ARGS "[-@ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1%]"
# define FT_ERRSTR "%s: %s: %s\n"

typedef struct stat		t_stat;
typedef struct timespec	t_time;
typedef struct passwd	t_pwd;
typedef struct group	t_grp;
typedef struct dirent	t_de;
typedef	struct			s_rec
{
	t_stat				*st;
	char				*path;
	char				*name;
	// char				path[__DARWIN_MAXPATHLEN];
	// char				name[__DARWIN_MAXNAMLEN];
	int					err_no;
	char				*err_str;
	char				*xattrs;
	char				*lnk_path;
	// char				xattrs[XATTR_MAXNAMELEN];
	// char				lnk_path[__DARWIN_MAXPATHLEN];
	struct s_rec		*lnk_to;
	acl_t				acl;
}						t_rec;
// typedef	struct			s_rec
// {
// 	// t_stat				*st;
// 	dev_t           st_dev;
// 	mode_t          st_mode;
// 	nlink_t         st_nlink;
// 	uid_t           st_uid;
// 	gid_t           st_gid;
// 	dev_t           st_rdev;
// 	struct  timespec st_atimespec;
// 	struct  timespec st_mtimespec;
// 	struct  timespec st_ctimespec;
// 	off_t           st_size;
// 	blkcnt_t        st_blocks;
// 	blksize_t       st_blksize;
// 	__uint32_t      st_flags;
// 	__uint32_t      st_gen;
// 	char				*path;
// 	char				*name;
// 	// char				path[__DARWIN_MAXPATHLEN];
// 	// char				name[__DARWIN_MAXNAMLEN];
// 	int					err_no;
// 	char				*err_str;
// 	char				*xattrs;
// 	char				*lnk_path;
// 	// char				xattrs[XATTR_MAXNAMELEN];
// 	// char				lnk_path[__DARWIN_MAXPATHLEN];
// 	struct s_rec		*lnk_to;
// 	acl_t				acl;
// }						t_rec;
typedef struct			s_datetime
{
	long				sec;
	long				min;
	long				hour;
	long				mday;
	long				mon;
	long				year;
	long				wday;
	long				yday;
	// char				*daystr;
	char				*monstr;
}						t_datetime;
typedef struct			s_vect
{
	void				**arr;
	// size_t				size;
	size_t				len;
	size_t				ilen;
	t_us				is_sorted;
	void				*(*arr_destroier)(void**);
}						t_vect;
typedef struct			s_maxvallen
{
	t_ull				lnk;
	t_ull				un;
	t_ull				gn;
	t_ull				sl;
	t_ull				maj;
	t_ull				min;
}						t_maxvallen;
typedef struct			s_dir
{
	DIR					*dir;
	t_de				*dirent;
	long				len;
	// t_rec				*content[LINK_MAX];
	t_rec				**content;
}						t_dir;

t_rec					*ft_new_rec(char *name, char path[MAXNAMLEN]);
int						ft_msort(t_vect *v, t_us asc, \
long long f(void*, void*));
void					ft_sort_recs(t_vect *arr, uint32_t flags);
void					ft_ls(t_vect *p, uint32_t f);
void					ft_print_all(t_vect *r, uint32_t *f, t_maxvallen mvl);
void					ft_print_files(t_vect *r, uint32_t *f, t_maxvallen mvl);
void					ft_print_dirs(t_vect *r, uint32_t *f);
t_vect					*ft_new_vect(/* size_t s,  */size_t l, \
void *arr_destroier(void**));
void					*ft_destroy_vect(t_vect **v);
void					*ft_destroy_rec(void **record);
t_maxvallen				ft_get_mvl(t_vect *vector, uint32_t flags);
void					ft_arr_cpy(void **dst, void **src, size_t len);
// t_us					ft_is_dir(mode_t m);
t_us					ft_is_dir(t_rec *m);
t_us					ft_is_spec(mode_t m);
t_us					ft_is_lnk(mode_t m);
t_us					ft_is_reg_file(mode_t m);
char					*ft_get_path(t_rec *r, char *dst);
char					*ft_get_lnk_path(t_rec *r, char *dst);
uint32_t				ft_get_flags(char ***av, int *len);
t_vect					*ft_get_params(char **av, int len);
void					ft_print_usage(char f, int exit_code);
char					ft_get_file_type(mode_t m);
void					ft_get_month_str(char *arr[12]);
void					ft_set_loc(t_datetime *dt);
// t_datetime				ft_localtime(t_time *t);
time_t					ft_difftime(time_t *t1, time_t *t2);
void					ft_print_user(uid_t id, t_ull un, uint32_t f);
char					*ft_get_user_name(uid_t id);
/*
** @todo: Compare perfomance betwin itoa and printf
** @todo: Implement ft_get_group_name and check perfomance
*/
void					ft_print_group(gid_t id, t_ull gn, uint32_t f);
char					*ft_get_group_name(gid_t id);
void					ft_print_rifo(t_rec *rd, uint32_t *f, t_maxvallen mvl);
int						ft_readdir(char *dname, uint32_t flags);
void					ft_print_all(t_vect *r, uint32_t *f, t_maxvallen mvl);
void					ft_perr(char *file, char *errstr);
void					ft_ls(t_vect *p, uint32_t f);
t_us					ft_is_hidden(uint32_t f, char *name);
long long				ft_sort_by_mtime(void *a, void *b);
long long				ft_sort_by_atime(void *a, void *b);
long long				ft_sort_by_ctime(void *a, void *b);
long long				ft_sort_by_utime(void *a, void *b);
long long				ft_sort_by_name(void *a, void *b);
void					ft_print_time(t_time t);
void					ft_print_owners(t_stat *st, t_maxvallen mvl,\
uint32_t f);
t_rec					*ft_new_clear_rec(void);
void					*ft_st_error(t_rec *r);
void					ft_rec_set_x(t_rec *r, char* p);

#endif
