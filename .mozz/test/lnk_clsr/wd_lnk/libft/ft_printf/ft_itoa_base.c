/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmentat <gmentat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:37:53 by gmentat           #+#    #+#             */
/*   Updated: 2020/01/03 22:21:23 by gmentat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t				intlen_base(unsigned long long nb,
		unsigned long long base)
{
	size_t					i;

	i = 1;
	while (nb >= base)
	{
		i++;
		nb /= base;
	}
	return (i);
}

static void					base_rot(char **ret)
{
	int						i;

	i = 0;
	while ((*ret)[i])
	{
		if ((*ret)[i] > '9')
			(*ret)[i] = (char)('a' + (*ret)[i] - '9' - 1);
		i++;
	}
}

static void					write_base(char **ret, \
		unsigned long long n, unsigned long long base)
{
	size_t					i;
	size_t					len;

	i = 1;
	len = intlen_base(n, base);
	if ((*ret)[0] == '-')
		len += 1;
	while (n >= base)
	{
		(*ret)[len - i] = (char)((n % base) + '0');
		n /= base;
		i++;
	}
	(*ret)[len - i] = (char)((n % base) + '0');
}

char						*ft_itoa_base(unsigned long long n, int base)
{
	char					*ret;

	ret = ft_strnew(100);
	if (base < 0)
		write_base(&ret, (unsigned long long)n, (unsigned long long)-base);
	else
		write_base(&ret, (unsigned long long)n, (unsigned long long)base);
	if (base > 10)
		base_rot(&ret);
	return (ret);
}
