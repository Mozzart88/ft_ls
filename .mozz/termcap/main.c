/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:22:59 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/26 17:38:49 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <curses.h>
// #include <termcap.h>
#include <curses.h>
#include <term.h>
#include <libc.h>
#include "ft_ls.h"

int	ftt_putchar(int c)
{
	ft_putchar(c);
	return (0);
}
int main(void)
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
	// t_uint	tabs;
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

	// if (margin < columns_count)
	// tparm_value = tparm(set_lr_margin, margin, margin);
	// putp(tparm_value);
	rows_count = d / (columns_count / margin) ? d / (columns_count / margin) : 1;
	++rows_count;
	i = 1;
	r = 0;
	c = 0;
	ft_printf("%d", lines_of_memory);
	while (i < d)
	{
		// tparm_value = tparm(cursor_address, r, c);
		tparm_value = tparm(column_address, c);
		tputs(tparm_value, 1, ftt_putchar);
		// sleep(1);
		ft_printf("%s%02d", string, i);
		r = i % rows_count ? r + 1 : 0;
		c = i / rows_count * margin;
		if (r)
		{
			tparm_value = tparm(cursor_down);
			tputs(tparm_value, 1, ftt_putchar);
			// sleep(1);
		}
		else
		{
			tparm_value = tparm(restore_cursor);
			tputs(tparm_value, 1, ftt_putchar);
			// sleep(1);
		}
		
		++i;
		if (i >= d)
		{
			// sleep(1);
			while (r < rows_count)
			{
				tparm_value = tparm(cursor_down);
				tputs(tparm_value, 1, ftt_putchar);
				++r;
				sleep(1);
			}

			// tparm_value = tparm(column_address, c);
			// tputs(tparm_value, 1, ftt_putchar);
		}
	}
	// tparm_value = tparm(cursor_address, rows_count, c);
	// tputs(tparm_value, 1, ftt_putchar);
	return (0);
}