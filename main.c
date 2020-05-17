/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 22:30:02 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/17 14:01:12 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
			ft_perr((char*)*(p->arr - 1), r->_errstr);
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
