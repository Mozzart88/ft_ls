/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 22:29:26 by mozzart           #+#    #+#             */
/*   Updated: 2020/04/23 01:19:30 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	merge(int arr[], int l[], int r[], int ll, int rl)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (i < ll && j < rl)
	{
		if (i < ll && l[i] <= r[j])
		{
			arr[k] = l[i];
			++i;
		}
		if (j < rl && r[j] <= l[i])
		{
			arr[k] = r[j];
			++j;
		}
		++k;
	}
	while (i < ll)
	{
		arr[k] = l[i];
		++i;
		++k;
	}
	while (j < rl)
	{
		arr[k] = r[j];
		++j;
		++k;
	}
	return;
}

void		ft_msort(void *arr[], t_us size)
{
	int	ll;
	int	rl;
	int	i;
	int l[size / 2];
	int r[size - (size / 2)];

	if (size < 2)
		return;
	ll = size / 2;
	rl = size - ll;

	i = 0;
	while (i < ll)
	{
		l[i] = (int)arr[i];
		++i;
	}
	i = 0;
	while (i < rl)
	{
		r[i] = (int)arr[ll + i];
		++i;
	}
	ft_msort(l, ll);
	ft_msort(r, rl);
	merge(arr, l, r, ll, rl);
	return;
}

/* 
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
	ft_msort(arr, s);
	if (ac == 3)
		ft_print_arr(arr, s);
		
	return (1);
} */