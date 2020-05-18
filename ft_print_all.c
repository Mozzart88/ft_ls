/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 11:48:46 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/18 15:25:00 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_print_total_blocks(t_vect *rd, uint32_t f)
{
	blkcnt_t	bc;
	size_t		i;
	t_rec		*r;

	bc = 0;
	i = 0;
	while (rd->len > i)
	{
		r = (t_rec*)rd->arr[i];
		if (!(f & AE_FLAGS) && r->name[0] == '.' && ++i)
			continue;
		bc += r->st->st_blocks;
		++i;
	}
	ft_printf("total %lld\n", bc);
}

void		ft_print_all(t_vect *r, uint32_t *f, t_maxvallen mvl)
{
	size_t		i;
	t_us		p;

	i = 0;
	if (*f & LF_FLAGS && (r->len > 2 || *f & AE_FLAGS))
		ft_print_total_blocks(r, *f);
	if (r->is_sorted == 0)
		ft_sort_recs(r, *f);
	while (i < r->len)
	{
		p = ft_is_hidden(f, ((t_rec*)(r->arr[i]))->name);
		if (*f & FT_ZP_BIT)
			*f ^= FT_ZP_BIT;
		if (*f & (UA_FLAG) && p != 2)
			ft_print_rifo((t_rec*)r->arr[i], f, mvl);
		else if (!p || *f & (AE_FLAGS ^ UA_FLAG) || *f & FT_F_BIT)
			ft_print_rifo((t_rec*)r->arr[i], f, mvl);
		++i;
	}
}
