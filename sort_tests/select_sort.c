/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 22:29:26 by mozzart           #+#    #+#             */
/*   Updated: 2020/04/22 23:08:50 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ssort(int arr[], int size)
{
	int	i;
	int	min;
	int	j;
	int	temp;

	i = 0;
	while (i < size - 1)
	{
		min = i;
		j = i + 1;
		while (j < size)
		{
			if (arr[j] < arr[min])
				min = j;
				++j;
		}
		temp = arr[min];
		arr[min] = arr[i];
		arr[i] = temp;
		++i;
		// ft_swap()
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
	ft_ssort(arr, s);
	if (ac == 3)
		ft_print_arr(arr, s);
		
	return (1);
}