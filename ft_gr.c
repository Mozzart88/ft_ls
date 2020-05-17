/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 10:16:57 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/17 18:49:14 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_group(gid_t id)
{
	t_grp *g;

	if (!(g = getgrgid(id)))
		return ;
	ft_printf("%6s", g->gr_name);
}

char	*ft_get_group_name(gid_t id)
{
	t_grp	*g;
	char	*name;
	char	buff[_SC_GETGR_R_SIZE_MAX * MAXLOGNAME];

	if (!(g = (t_grp*)malloc(sizeof(t_grp))))
		return (NULL);
	if ((getgrgid_r(id, g, buff, _SC_GETGR_R_SIZE_MAX * MAXLOGNAME, &g)) || !g)
		name = ft_itoa_long_un(id);
	else
		name = ft_strdup(g->gr_name);
	g->gr_mem = NULL;
	g->gr_passwd = NULL;
	g->gr_name = NULL;
	g->gr_gid = 0;
	free(g);
	g = NULL;
	return (name);
}
