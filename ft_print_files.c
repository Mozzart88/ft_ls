/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 12:13:17 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/20 20:27:18 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_files(t_vect *r, uint32_t *f, t_maxvallen mvl)
{
	size_t		i;
	t_us		p;
	t_rec		*rec;
	char		ft;

	i = 0;
	if (r->is_sorted == 0)
		ft_sort_recs(r, *f);
	while (i < r->len)
	{
		rec = ((t_rec*)(r->arr[i]));
		p = ((t_rec*)(r->arr[i]))->name[0] == '.' ? 1 : 0;
		// if (*f & FT_ZP_BIT)
		// 	p = 0;
		if (!p || *f & AE_FLAGS)
		{
			ft = ft_get_file_type(rec->st->st_mode);
			if (ft != 'd' && (ft != 'l' || *f & LF_FLAGS))
				ft_print_rifo((t_rec*)r->arr[i], f, mvl);
			// else if (ft == 'l' && !(ft_is_dir(rec->lnk_to->st->st_mode)))
			else if (ft == 'l' && !(ft_is_dir(rec->lnk_to)))
				ft_print_rifo((t_rec*)r->arr[i], f, mvl);
		}
		++i;
	}
}
