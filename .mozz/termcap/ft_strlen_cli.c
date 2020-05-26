/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_cli.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 09:09:22 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/26 09:44:21 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	size_t	l;
	char	*buff;

	l = 0;
	if (ac == 2)
		l = ft_strlen(av[1]);
	else
		while ((get_next_line(0, &buff) > 0) && (l += ft_strlen(buff)))
			ft_strdel(&buff);
	ft_printf("%d\n", l);
	return (0);
}
