/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 10:07:32 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/19 18:19:50 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* 
** @todo: See group functions todo
*/
void		ft_print_user(uid_t id, t_ull un, uint32_t f)
{
	char *p;

	if (!(f & G_FLAG))
	{
		if (f & N_FLAG)
			p = ft_itoa_long_un(id);
		else
			p = ft_get_user_name(id);
		ft_printf("%-*s ", un + 1, p);
		ft_strdel(&p);
	}
}

char		*ft_get_user_name(uid_t id)
{
	t_pwd	*p;
	char	*name;

	if (!(p = getpwuid(id)))
		name = ft_itoa_long_un(id);
	else
		name = ft_strdup(p->pw_name);
	return (name);
}
