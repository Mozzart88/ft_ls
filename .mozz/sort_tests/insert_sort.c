/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 22:29:26 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/21 12:43:54 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_isort(void *arr[], int size)
{
	int	i;
	int	j;
	char	*temp;

	i = 1;
	while (i < size)
	{
		temp = arr[i];
		j = i;
		while (j > 0 && ft_strcmp(arr[j - 1], temp) > 0)
		{
				arr[j] = arr[j - 1];
			--j;
		}
		arr[j] = temp;
		++i;
	}
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

int main(int ac, char **av)
{
	// int a;
	// int s;
	// int arr[__SHRT_MAX__];

	// a = 0;
	// if (ac > 1)
	// 	s = ft_atoi(av[1]);
	// else
	// 	s = __SHRT_MAX__;	
	// while (a < s)
	// {
	// 	arr[a] = s - a;
	// 	++a;
	// }
	// if (ac == 3)
		// ft_print_arr((void**)(av + 1), ac - 1);
	ft_isort((void**)(av + 1), ac - 1);
	// if (ac == 3)
		// ft_print_arr((void**)(av + 1), ac - 1);
		
	return (1);
}