/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_pointers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 15:44:59 by mozzart           #+#    #+#             */
/*   Updated: 2020/04/23 15:51:50 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap_pointers(void* arr[])
{
	void	*temp;
	// t_ull	**a;

	// a = (t_ull)arr;
	temp = arr[0];
	arr[0] = arr[1];
	arr[1] = temp;
	return;
}

void	ft_print_arr(void *arr[], int s)
{
	int i;

	i = 0;
	while (i < s)
	{
		ft_printf("%d => %s\n", i, (char*)arr[i]);
		++i;
	}
	return;
}


int		main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	ft_print_arr((void**)av, ac);
	ft_swap_pointers((void**)av);
	ft_print_arr((void**)av, ac);
	return (0);
}