/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_long_un.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmentat <gmentat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:35:39 by gmentat           #+#    #+#             */
/*   Updated: 2019/12/25 17:46:01 by gmentat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t		ft_itoa_len(unsigned long long n)
{
	size_t	r;

	if (n == 0)
		return (1);
	r = 0;
	while (n)
	{
		n /= 10;
		r++;
	}
	return (r);
}

char				*ft_itoa_long_un(unsigned long long n)
{
	size_t	l;
	size_t	e;
	char	*r;

	e = 0;
	l = ft_itoa_len(n);
	if (!(r = (char *)malloc(l + 1)))
		return (NULL);
	r[l] = '\0';
	while (l-- > e)
	{
		r[l] = '0' + n % 10;
		n /= 10;
	}
	return (r);
}
