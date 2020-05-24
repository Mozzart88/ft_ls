/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:41:10 by tvanessa          #+#    #+#             */
/*   Updated: 2020/01/06 22:12:26 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		ft_itoa_len(int n)
{
	size_t	r;

	if (!n)
		return (1);
	r = 0;
	if (n < 0)
		++r;
	while (n)
	{
		n /= 10;
		++r;
	}
	return (r);
}

char				*ft_itoa(int n)
{
	size_t	l;
	size_t	e;
	char	*r;

	e = 0;
	r = NULL;
	l = ft_itoa_len(n);
	if (!(r = (char *)malloc(l + 1)))
		return (NULL);
	r[l] = 0;
	if (n < 0)
	{
		r[0] = 45;
		e = 1;
	}
	while (l-- > e)
	{
		r[l] = 48 + n % 10 * (n < 0 ? -1 : 1);
		n /= 10;
	}
	return (r);
}
