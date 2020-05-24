/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:37:53 by gmentat           #+#    #+#             */
/*   Updated: 2020/05/17 16:16:48 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	intlen_base(t_ull nb, t_ull base)
{
	size_t	i;

	i = 1;
	while (nb >= base)
	{
		i++;
		nb /= base;
	}
	return (i);
}

static void		base_rot(char **ret)
{
	int	i;

	i = 0;
	while ((*ret)[i])
	{
		if ((*ret)[i] > '9')
			(*ret)[i] = (char)('a' + (*ret)[i] - '9' - 1);
		i++;
	}
}

static void		write_base(char **ret, t_ull n, t_ull base)
{
	size_t	i;
	size_t	len;

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

char			*ft_itoa_base(t_ull n, int base)
{
	char					*ret;

	ret = ft_strnew(100);
	if (base < 0)
		write_base(&ret, (t_ull)n, (t_ull)-base);
	else
		write_base(&ret, (t_ull)n, (t_ull)base);
	if (base > 10)
		base_rot(&ret);
	return (ret);
}
