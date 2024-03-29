/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 08:25:36 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/22 05:37:20 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		ft_is_legal_flag(char *f)
{
	if (ft_strequ(f, "--"))
		return (1);
	if (f[0] != '-' && STRICT_FLAGS_ORDER)
		return (2);
	if (ft_strlen(f) <= 1)
		return (2);
	return (0);
}

static uint32_t	ft_get_mask(uint32_t f, t_us offset)
{
	uint32_t		b;
	static uint32_t	gob = 0x0;

	b = (1 << offset);
	if (b & 0x20008)
		gob |= b;
	if (b & 0x420 && f & 0x420)
		f ^= (f & 0x420);
	if (b & 0x20408 && f & 0x20408)
	{
		f ^= (f & 0x20408);
		if (b & 0x20008)
			b |= gob;
	}
	if (b & (AE_FLAGS | UA_FLAG))
	{
		if (f & AE_FLAGS)
			return (f);
		if (f & UA_FLAG)
			f ^= UA_FLAG;
	}
	if (b & 0x18200 && f & 0x18200)
		f ^= (f & 0x18200);
	return (f | b);
}

static uint32_t	ft_parse_flag(uint32_t f, char *av)
{
	char *ai;

	while (*av)
	{
		if (!(ai = ft_strchr(LETER_FLAGS, *av)))
			ft_print_usage(*av, 1);
		f = ft_get_mask(f, (ai - LETER_FLAGS));
		++av;
	}
	return (f);
}

uint32_t		ft_get_flags(char ***av, int *len)
{
	uint32_t	r;
	int			lf;

	r = 0;
	while (*len)
	{
		if ((lf = ft_is_legal_flag(**av)) != 0)
		{
			if (lf == 1)
			{
				--*len;
				++*av;
			}
			break ;
		}
		++**av;
		r = ft_parse_flag(r, **av);
		++*av;
		--*len;
	}
	return (r);
}

t_vect			*ft_get_params(char **av, int len)
{
	int		i;
	t_vect	*v;

	i = 0;
	if (!len)
	{
		++len;
		av[0] = ".";
	}
	if (!(v = ft_new_vect(len, NULL)))
		return (NULL);
	while (len--)
	{
		v->arr[i] = *av;
		++av;
		++i;
	}
	return (v);
}
