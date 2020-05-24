/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 09:42:03 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/18 21:27:45 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_print_usage(char f, int exit_code)
{
	char	c;

	c = ft_isprint(f) ? f : 0;
	ft_dprintf(2, FT_PUSAGE, FT_PROG_NAME, c, FT_PUSAGE_ARGS);
	exit(exit_code);
}

void			ft_perr(char *file, char *errstr)
{
	ft_dprintf(2, FT_ERRSTR, FT_PROG_NAME, file, errstr);
}
