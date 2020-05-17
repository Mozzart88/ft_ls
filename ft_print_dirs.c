/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 12:35:54 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/17 14:01:35 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_us		ft_is_hidden(uint32_t f, char *name)
{
	t_us	p;

	if (AE_FLAGS & f)
		p = ft_strequ(name, ".") ? 1 : ft_strequ(name, "..");
	else
		p = name[0] == '.' ? 1 : 0;
	if ((f & 0x800))
		p = 0;
	return (p);
}

static	void	ft_print_content(uint32_t f, t_rec *r, size_t l)
{
	char	*en;
	char	n[__DARWIN_MAXPATHLEN];
	int		e;

	ft_get_path(r, n);
	if (f & 0x1000 && l > 1)
		ft_printf("%s:\n", n);
	else if (l > 1)
		ft_printf("\n%s:\n", n);
	if ((e = ft_readdir(n, f & UR_FLAG ? f & 0x7FF : (f & 0x7FF) | D_FLAG)))
	{
		en = ft_is_lnk(r->st->st_mode) ? r->lnk_to->name : r->name;
		ft_perr(en, strerror(e));
	}
}

void			ft_print_dirs(t_vect *v, uint32_t *f)
{
	size_t		i;
	t_us		p;
	t_rec		*r;
	char		ft;

	if (v->is_sorted == 0)
		ft_sort_recs(v, *f);
	i = 0;
	while (i < v->len)
	{
		r = (t_rec*)v->arr[i];
		p = ft_is_hidden(*f, r->name);
		ft = ft_get_file_type(r->st->st_mode);
		if (!(*f & D_FLAG) && (p == 0))
		{
			if (ft == 'd')
				ft_print_content(*f, (t_rec*)v->arr[i], v->ilen);
			else if (ft == 'l')
				if (ft_is_dir(r->lnk_to->st->st_mode) && !(*f & LF_FLAGS))
					ft_print_content(*f, (t_rec*)v->arr[i], v->ilen);
		}
		*f &= 0xFFF;
		++i;
	}
}