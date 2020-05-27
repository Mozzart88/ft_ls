/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plain_uotput.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:22:59 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/27 13:41:33 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ftt_putchar(int c)
{
	ft_putchar(c);
	return (0);
}

static int	ft_get_sizes(t_term_sizes *s, t_ull n, size_t l, uint32_t f)
{
	int t;

	if (!(s->cc = columns) || !(t = TABSIZE))
		return (1);
	if (!(s->tc = n % t ? t - n % t + n : n + t))
		return (1);
	if (f & UG_FLAG && s->tc)
		--s->tc;
	s->tr = (l / (s->cc / s->tc));
	if (s->tr == 0 || l % s->tr)
		++s->tr;
	return (0);
}

int		ft_plain_output(t_vect *v, t_maxvallen mvl, uint32_t f)
{
	char			b[1024];
	t_uint			i;
	t_term_sizes	sizes;
	t_uint			coords[2];

	if ((tgetent(b, getenv("TERM"))) <= 0)
		return (1);
	tputs(tparm(save_cursor), 1, ftt_putchar);
	// putp(tparm(cursor_visible));
	if (ft_get_sizes(&sizes, mvl.name, v->len, f))
		return (1);
	i = 1;
	coords[1] = 0;
	coords[0] = 0;
	while (i <= v->len)
	{
		tputs(tparm(column_address, coords[0]), 1, ftt_putchar);
		ft_print_filename((t_rec*)(v->arr[i - 1]), f);
		coords[1] = i % sizes.tr;
		coords[0] = i / sizes.tr * sizes.tc;
		if (!coords[1])
			tputs(tparm(restore_cursor), 1, ftt_putchar);
		++i;
	}
	while (++coords[1] <= sizes.tr)
		tputs(tparm(cursor_down), 1, ftt_putchar);
	tputs(tparm(column_address, 0), 1, ftt_putchar);
	// reset_shell_mode();
	return (0);
}
