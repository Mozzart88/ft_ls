/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 21:01:43 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/05 20:17:13 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_sort_by_name(t_rec **arr, t_us l)
{
	if (arr || l)
		return ;
}

static void		ft_sort_by_mtime(t_rec **arr, t_us l)
{
	if (arr || l)
		return ;
}

static void		ft_sort_by_atime(t_rec **arr, t_us l)
{
	if (arr || l)
		return ;
}

static void		ft_sort_by_type(t_rec **arr, t_us l)
{
	if (arr || l)
		return ;
}

void		ft_sort_by_size()
{
	return ;
}

void		ft_sort_recs(t_rec **arr, uint32_t f, t_us l)
{
	if (f & F_FLAG)
		return ;
	ft_sort_by_type(arr, l);
	if (f & T_FLAG)
		ft_sort_by_mtime(arr, l);
	if (f & U_FLAG)
		ft_sort_by_atime(arr, l);
	ft_sort_by_name(arr, l);
}
