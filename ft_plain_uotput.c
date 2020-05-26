/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plain_uotput.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:22:59 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/26 19:02:11 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <curses.h>
// #include <termcap.h>
#include <curses.h>
#include <term.h>
#include <libc.h>
#include "ft_ls.h"

static int	ftt_putchar(int c)
{
	ft_putchar(c);
	return (0);
}

void ft_plain_output(void)
{
	char	b[1024];
	char	*tparm_value;
	char	*string;
	t_uint	i;
	t_uint	j;
	t_uint	d;
	t_uint	columns_count;
	t_uint	rows_count;
	int	c;
	int	r;
	t_uint	margin;
	size_t	str_max_len;

	d = 30;
	string = "string";
	tgetent(b, getenv("TERM"));
	tparm_value = tparm(save_cursor);
	tputs(tparm_value, 1, ftt_putchar);
	tparm_value = tparm(cursor_visible);
	putp(tparm_value);
	str_max_len = ft_strlen(string) + 2;
	columns_count = columns;
	margin = str_max_len % TABSIZE ? TABSIZE - str_max_len % TABSIZE + str_max_len : str_max_len + TABSIZE;
	rows_count = d / (columns_count / margin) ? d / (columns_count / margin) : 1;
	++rows_count;
	i = 1;
	r = 0;
	c = 0;
	ft_printf("%d", lines_of_memory);
	while (i < d)
	{
		tparm_value = tparm(column_address, c);
		tputs(tparm_value, 1, ftt_putchar);
		ft_printf("%s%02d", string, i);
		r = i % rows_count;
		c = i / rows_count * margin;
		if (r)
			tputs(tparm(cursor_down), 1, ftt_putchar);
		else
			tputs(tparm(restore_cursor), 1, ftt_putchar);
		++i;
		if (i >= d)
			while (++r <= rows_count)
				tputs(tparm(cursor_down), 1, ftt_putchar);
	}
	return (0);
}