/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:40:44 by tvanessa          #+#    #+#             */
/*   Updated: 2019/09/11 18:01:30 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char		*r;
	size_t		cs;
	size_t		l;
	size_t		i;

	r = NULL;
	if (!s || !f)
		return (r);
	cs = sizeof(char);
	l = ft_strlen(s);
	if (!(r = ft_strnew(l)))
		return (r);
	i = 0;
	while (i < l)
	{
		r[i] = (f)(s[i]);
		++i;
	}
	return (r);
}
