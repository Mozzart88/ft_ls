/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plain_uotput.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:22:59 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/26 21:32:05 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ftt_putchar(int c)
{
	ft_putchar(c);
	return (0);
}

void ft_plain_output(t_vect *v, t_maxvallen mvl, uint32_t f)
{
	char	b[1024];
	t_uint	i;
	t_uint	sizes[3];
	t_uint	coords[2];
	int		tabs;

	tgetent(b, getenv("TERM"));
	tputs(tparm(save_cursor), 1, ftt_putchar);
	putp(tparm(cursor_visible));
	sizes[0] = columns;
	tabs = TABSIZE;
	sizes[2] = mvl.name % tabs ? tabs - mvl.name % tabs + mvl.name : mvl.name + tabs;
	if (f & UG_FLAG)
		--sizes[2];
	sizes[1] = v->len / (sizes[0] / sizes[2]) ? (v->len / (sizes[0] / sizes[2])) + 1 : 1;
	i = 1;
	coords[1] = 0;
	coords[0] = 0;
	while (i <= v->len)
	{
		tputs(tparm(column_address, coords[0]), 1, ftt_putchar);
		ft_print_filename((t_rec*)(v->arr[i - 1]), f);
		coords[1] = i % sizes[1];
		coords[0] = i / sizes[1] * sizes[2];
		if (!coords[1])
			tputs(tparm(restore_cursor), 1, ftt_putchar);
		++i;
	}
	while (++coords[1] <= sizes[1])
		tputs(tparm(cursor_down), 1, ftt_putchar);
	tputs(tparm(column_address, 0), 1, ftt_putchar);
}