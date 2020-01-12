/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 22:30:02 by tvanessa          #+#    #+#             */
/*   Updated: 2020/01/12 20:48:47 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


int		main(int ac, char **av)
{
	char	*dname;
	t_us	i;
	DIR		*d;
	t_de	*dc;

	i = 0;
	while (i < ac)
	{
		if (ac == 1 && ++i)
			dname = ".";
		else
			dname = av[++i];
		if ((d = opendir(dname)))
			while ((dc = readdir(d)))
			{
				ft_printf("%s -> ", dc->d_name);
				dc->d_type == 8 ? ft_printf("file\n") : ft_printf("dir\n");
			}
		closedir(d);
	}	
	return (0);
}
