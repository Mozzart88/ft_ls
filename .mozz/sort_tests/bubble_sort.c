/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 22:29:26 by mozzart           #+#    #+#             */
/*   Updated: 2020/04/22 23:16:41 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bsort(int arr[], int size)
{
	int	i;
	int	is_sorted;
	int	temp;

	is_sorted = 0;
	while (!is_sorted)
	{
		i = 0;
		is_sorted = 1;
		while (i < size - 1)
		{
			if (arr[i] > arr[i + 1])
			{
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				is_sorted = 0;
			}
			++i;
		}
	}
	return;
}

void	ft_print_arr(int arr[], int s)
{
	int i;

	i = 0;
	while (i < s)
	{
		ft_printf("%d => %d\n", i, arr[i]);
		++i;
	}
	return;
}

int main(int ac, char **av)
{
	int a;
	int s;
	int arr[__SHRT_MAX__];

	a = 0;
	if (ac > 1)
		s = ft_atoi(av[1]);
	else
		s = __SHRT_MAX__;	
	while (a < s)
	{
		arr[a] = s - a;
		++a;
	}
	if (ac == 3)
		ft_print_arr(arr, s);
	ft_bsort(arr, s);
	if (ac == 3)
		ft_print_arr(arr, s);
		
	return (1);
}