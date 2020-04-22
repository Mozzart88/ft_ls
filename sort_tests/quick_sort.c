/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 22:29:26 by mozzart           #+#    #+#             */
/*   Updated: 2020/04/23 00:26:08 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_swap(int *a, int *b)
{
	int t;

	t = *a;
	*a = *b;
	*b = t;
}

static int	partision(int arr[], int start, int end)
{
	int pivot;
	int pIndex;
	int i;

	pivot = arr[end];
	pIndex = start;
	i = start;
	while (i < end)
	{
		if (arr[i] <= pivot)
		{
			ft_swap(&arr[i], &arr[pIndex]);
			++pIndex;
		}
		++i;
	}
	ft_swap(&arr[end], &arr[pIndex]);
	return (pIndex);
}

void		ft_qsort(int arr[], int start, int size)
{
	int i;

	if (start < size)
	{
		i = partision(arr, start, size);
		ft_qsort(arr, start, i - 1);
		ft_qsort(arr, i + 1, size);
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
	ft_qsort(arr, 0, s - 1);
	if (ac == 3)
		ft_print_arr(arr, s);
		
	return (1);
}