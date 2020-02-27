/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 21:01:43 by tvanessa          #+#    #+#             */
/*   Updated: 2020/02/27 21:02:58 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_sort_by_name()
{
	return ;
}

void		ft_sort_by_mtime()
{
	return ;
}

void		ft_sort_by_atime()
{
	return ;
}

void		ft_sort_by_size()
{
	return ;
}

void		ft_sort(t_rec **arr, uint32_t f, t_us l)
{
	if (arr || f || l)
		return ;
}

void		ft_swap(int *a, int *b)
{
	int	*t;

	t = a;
	a = b;
	b = t;
	return ;
}

void		ft_insertionSort(int arr[], int *s, int *e)
{
	int	left;
	int right;
	int	i;
	int	key;
	int j;
	
	left = e - arr;
	right = s - arr;
	i = left + 1;
	while (i <= right)
	{
		key = arr[i];
		j = i - 1;
		while (j >= left && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			--j;
		}
		++i;
	}
	return ;
}

int		*ft_partition(int arr[], int low, int high)
{
	int pivot;
	int i;
	int j;

	pivot = arr[high];
	i = (low - 1);
	j = low;
	while (j <= pivot)
	{
		if (arr[j] <= pivot)
		{
			++i;
			ft_swap(arr[i], arr[j]);
		}
		++j;
	}
	ft_swap(arr[i + 1], arr[j + 1]);
	return (arr + i + 1);
}

int		*ft_medianOfThree(int *a, int *b , int *c)
{
	if (*a < *b && *b < *c)
		return (b);
	if (*a < *c && *c <= *b)
		return (c);
	if (*b <= *a && *a < *c)
		return (a);
	if (*b < *c && *c <= *a)
		return (c);
	if (*c <= *a && *a < *b)
		return (a);
	if (*c <= *b && *b < *a)
		return (b);
}

void	ft_introsortUtil(int arr[], int *s, int *e, int depthLimit)
{
	int size;
	int *pivot; 
	int *partition_point;

	size = e - s;
	if (size < 16)
	{
		ft_insertionSort(arr, s, e);
		return ;
	}
	if (depthLimit == 0)
	{
		ft_make_heap(s, e + 1);
		ft_sort_heap(s, e + 1);
		return ;
	}
	pivot = ft_medianOfThree(s, s + size/2, e);
	ft_swap(pivot, e);
	partition_point = ft_partition(arr, s - arr, e - arr);
	ft_introsortUtil(arr, s, partition_point - 1, depthLimit - 1);
	ft_introsortUtil(arr, s, partition_point + 1, depthLimit - 1);
	return ;
}

void	introsort(int arr[], int *s, int *e)
{
	int	depth_limit;

	depth_limit = 2 * log(e - s);
	ft_introsortUtil(arr, s, e, depth_limit);
	return ;
}