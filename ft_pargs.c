/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 08:25:36 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/17 09:42:29 by mozzart          ###   ########.fr       */
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

static uint32_t	ft_get_mask(uint32_t r, t_us offset)
{
	uint32_t	b;

	b = (1 << offset);
	if (b & 0x420 && r & 0x420)
		r ^= (r & 0x420);
	if (b & 0x408 && r & 0x408)
		r ^= (r & 0x408);
	return (r | b);
}

static uint32_t	ft_parse_flag(uint32_t r, char *av)
{
	char *ai;

	while (*av)
	{
		if (!(ai = ft_strchr(LETER_FLAGS, *av)))
			ft_print_usage(*av, 1);
		r = ft_get_mask(r, (ai - LETER_FLAGS));
		++av;
	}
	return (r);
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
	if (!(v = ft_new_vect(sizeof(char*), len, NULL)))
		return (NULL);
	while (len--)
	{
		v->arr[i] = *av;
		++av;
		++i;
	}
	return (v);
}
