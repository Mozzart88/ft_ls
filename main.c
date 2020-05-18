/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 22:30:02 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/18 20:52:14 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_print_owners(t_stat *st, t_maxvallen mvl, uint32_t f)
{
	if (f & G_FLAG && f & O_FLAG)
		ft_printf("  ");
	else
	{
		ft_print_user(st->st_uid, mvl.un, f);
		ft_print_group(st->st_gid, mvl.gn, f);
	}
}

static long long	ft_strcmp_s(void *a, void *b)
{
	return (ft_strcmp((char*)a, (char*)b));
}

int					main(int ac, char **av)
{
	t_us		i;
	uint32_t	flags;
	t_vect		*params;

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
