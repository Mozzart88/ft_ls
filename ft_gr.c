/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 10:16:57 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/24 12:34:09 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_group(gid_t id, t_ull gn, uint32_t f)
{
	char *g;

	if (!(f & O_FLAG))
	{
		if (f & N_FLAG)
			g = ft_itoa_long_un(id);
		else
			g = ft_get_group_name(id);
		ft_printf("%*s", -(gn + 2), g);
		ft_strdel(&g);
	}
}

char	*ft_get_group_name(gid_t id)
{
	char			*name;
	static t_grp	*g = NULL;

	if (g && g->gr_gid == id)
		name = ft_strdup(g->gr_name);
	else if (!(g = getgrgid(id)))
		name = ft_itoa_long_un(id);
	else
		name = ft_strdup(g->gr_name);
	return (name);
}
