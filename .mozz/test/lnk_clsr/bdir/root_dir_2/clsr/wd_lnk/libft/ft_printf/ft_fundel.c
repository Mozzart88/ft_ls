/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fundel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmentat <gmentat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:21:45 by gmentat           #+#    #+#             */
/*   Updated: 2020/01/07 15:46:59 by gmentat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_fundel(char *app, char *str, int z, int t)
{
	char	*dup;
	int		la;
	int		ls;

	la = ft_strlen(app);
	ls = ft_strlen(str);
	if (!(dup = ft_strnew(la + ls)))
		return (NULL);
	if ((z == 2 && t == 1) || z == 1)
	{
		ft_strcpy(dup, str);
		ft_strcpy(dup + ls, app);
	}
	if ((z == 2 && t == 0) || z == 0)
	{
		ft_strcpy(dup, app);
		ft_strcpy(dup + la, str);
	}
	ft_strdel(&app);
	if (z == 0 || z == 1)
		ft_strdel(&str);
	return (dup);
}
