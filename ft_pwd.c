/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 10:07:32 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/17 10:16:33 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_user(uid_t id)
{
	t_pwd *p;

	if (!(p = getpwuid(id)))
		return ;
	ft_printf("%9s", p->pw_name);
}

char	*ft_get_user_name(uid_t id)
{
	t_pwd	*p;
	char	*name;
	char	buff[_SC_GETPW_R_SIZE_MAX];

	if (!(p = (t_pwd*)malloc(sizeof(t_pwd))))
		return (NULL);
	if ((getpwuid_r(id, p, buff, _SC_GETPW_R_SIZE_MAX, &p)) || !p)
		name = ft_itoa_long_un(id);
	else
		name = ft_strdup(p->pw_name);
	if (p)
	{
		p->pw_name = NULL;
		p->pw_passwd = NULL;
		p->pw_class = NULL;
		p->pw_gecos = NULL;
		p->pw_dir = NULL;
		p->pw_shell = NULL;
		p->pw_change = 0;
		p->pw_expire = 0;
		p->pw_uid = 0;
		p->pw_gid = 0;
		ft_free((void**)p);
	}
	return (name);
}
