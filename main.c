/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 22:30:02 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/17 12:17:07 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
