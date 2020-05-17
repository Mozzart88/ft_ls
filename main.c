/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 22:30:02 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/17 11:51:39 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


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

 void 	ft_print_files(t_vect *r, uint32_t *f, t_maxvallen mvl)
{
	size_t		i;
	t_us		p;
	t_rec		*rec;

	i = 0;
	if (r->is_sorted == 0)
		ft_sort_recs(r, *f);
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

void 	ft_print_dirs(t_vect *r, uint32_t *f)
{
	size_t		i;
	char		name[__DARWIN_MAXPATHLEN];
	t_us		p;
	int			e;

	i = 0;
	if (r->is_sorted == 0)
		ft_sort_recs(r, *f);
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
				if ((e = ft_readdir(name, *f & UR_FLAG ? *f & 0x7FF : (*f & 0x7FF) | D_FLAG)))
					ft_dprintf(2, "ft_ls: %s: %s\n", ((t_rec*)(r->arr[i]))->lnk_to->name, strerror(e));
			}
		}
		*f &= 0xFFF;
		++i;
	}
}

void	ft_ls(t_vect *p, uint32_t f)
{
	t_us	i;
	t_vect	*v;
	t_rec	*r;
	t_maxvallen mvl;

	i = 0;
	if (!(v = ft_new_vect(sizeof(t_rec), p->len, ft_destroy_rec)))
		return ;
	while (i < v->len)
	{
		r = ft_new_rec((char*)*(p->arr), "");
		++p->arr;
		if (r->_errno)
		{
			ft_dprintf(2, "ls: %s: %s\n", (char*)*(p->arr - 1), r->_errstr);
			ft_destroy_rec((void**)&r);
			--v->len;
			continue;
		}
		v->arr[i] = r;
		++i;
	}
	f |= 0x1800;
	mvl = ft_new_mvl(v, f);
	if (f & D_FLAG)
		ft_print_all(v, &f, mvl);
	else
	{
		ft_print_files(v, &f, mvl);
		ft_print_dirs(v, &f);
	}
	p->arr = p->arr - p->len;
	p->len = i;
	ft_destroy_vect(&v);
	return;
}

static long long ft_strcmp_s(void* a, void* b)
{
	return (ft_strcmp((char*)a, (char*)b));
}

int		main(int ac, char **av)
{
	t_us	i;
	uint32_t	flags;
	t_vect	*params;

	i = ac;
	++av;
	--ac;
	flags = ft_get_flags(&av, &ac);
	params = ft_get_params(av, ac);
	if (!(flags & F_FLAG))
		ft_msort(params, 0, ft_strcmp_s);
	ft_ls(params, flags);
	ft_destroy_vect(&params);
	return (0);
}
