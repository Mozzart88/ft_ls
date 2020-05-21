/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 12:35:54 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/20 19:43:02 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_us			ft_is_hidden(uint32_t f, char *name)
{
	t_us	p;

	if (f & (FT_ZP_BIT | AE_FLAGS))
		return (0);
	if (f & UA_FLAG)
		return (ft_strequ(name, ".") ? 1 : ft_strequ(name, ".."));
	return (name[0] == '.' ? 1 : 0);
	return (p);
}

t_us			ft_is_pdir(uint32_t f, char *name)
{
	if (f & (FT_ZP_BIT))
		return (0);
	return (ft_strequ(name, ".") ? 1 : ft_strequ(name, ".."));
}

static	void	ft_print_content(uint32_t f, t_rec *r, size_t l)
{
	char		*en;
	char		n[__DARWIN_MAXPATHLEN];
	int			e;
	uint32_t	ff;

	ft_get_path(r, n);
	if (f & FT_F_BIT && l > 1)
		ft_printf("%s:\n", n);
	else if (l > 1)
		ft_printf("\n%s:\n", n);
	ff = f & UR_FLAG ? f & FT_ALL_PFLAGS : (f & FT_ALL_PFLAGS) | D_FLAG;
	if ((e = ft_readdir(n, ff)))
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
	// uint32_t	ff;

	if (v->is_sorted == 0)
		ft_sort_recs(v, *f);
	i = 0;
	// ff = *f | UA_FLAG;
	while (i < v->len)
	{
		r = (t_rec*)v->arr[i];
		p = ft_is_pdir(*f, r->name);
		p = p ? p : ft_is_hidden(*f, r->name);
		ft = ft_get_file_type(r->st->st_mode);
		if (!(*f & D_FLAG) && (p == 0) && (ft == 'd' || ft == 'l'))
		{
			if (ft == 'l')
			{
				// if (ft_is_dir(r->lnk_to->st->st_mode) && !(*f & LF_FLAGS))
				if (ft_is_dir(r->lnk_to) && !(*f & LF_FLAGS))
					ft_print_content(*f, (t_rec*)v->arr[i], v->ilen);

			}
			else
				ft_print_content(*f, (t_rec*)v->arr[i], v->ilen);
			// if (ft == 'd')
			ft_destroy_rec((void**)&v->arr[i]);
			v->arr[i] = NULL;
		}
		*f &= FT_ALL_FLAGS;
		++i;
	}
}
