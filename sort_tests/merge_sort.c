/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 22:29:26 by mozzart           #+#    #+#             */
/*   Updated: 2020/04/23 17:06:11 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_swap_pointers(char **a, char **b)
{
	char	*t;

	t = *a;
	*a = *b;
	*b = t;
	return;
}

static void	merge(char *arr[], char *l[], char *r[], int ll, int rl)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (i < ll && j < rl)
	{
		if (ft_strcmp(l[i], r[j]) <= 0)
		{
			ft_swap_pointers(&arr[k], &l[i]);
			++i;
		}
		else
		{
			ft_swap_pointers(&arr[k], &r[j]);
			++j;
		}
		++k;
	}
	while (i < ll)
	{
		ft_swap_pointers(&arr[k], &l[i]);
		++i;
		++k;
	}
	while (j < rl)
	{
		ft_swap_pointers(&arr[k], &r[j]);
		++j;
		++k;
	}
	return;
}

void		ft_msort(void *arr[], int size)
{
	int	ll;
	int	rl;
	int	i;
	void *l[size / 2];
	void *r[size - (size / 2)];

	if (size < 2)
		return;
	ll = size / 2;
	rl = size - ll;

	i = 0;
	while (i < ll)
	{
		// l[i] = ft_strdup(arr[i]);
		l[i] = arr[i];
		++i;
	}
	i = 0;
	while (i < rl)
	{
		// r[i] = ft_strdup(arr[ll + i]);
		r[i] = arr[ll + i];
		++i;
	}
	ft_msort(l, ll);
	ft_msort(r, rl);
	merge((char**)arr, (char**)l, (char**)r, ll, rl);
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
	ft_print_arr((void**)av, ac);
	ft_msort((void**)av, ac);
	ft_print_arr((void**)av, ac);
	return (0);
}