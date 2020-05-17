/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 09:42:03 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/17 09:43:06 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_print_usage(char f, int exit_code)
{
	if (ft_isprint(f))
		ft_dprintf(2, FT_PUSAGE, f);
	else
		ft_dprintf(2, FT_PUSAGE, 0);
	exit(exit_code);
}
