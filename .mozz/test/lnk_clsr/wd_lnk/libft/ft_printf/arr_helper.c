/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 12:56:29 by tvanessa          #+#    #+#             */
/*   Updated: 2020/01/06 19:55:19 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				ft_clear_arr(t_us *arr, size_t len)
{
	while (len--)
		arr[len] = 0;
}

t_us				*ft_arrcpy(t_us *dst, t_us *src, t_us len)
{
	while (len--)
		dst[len] = src[len];
	return (dst);
}

t_us				*ft_arr_add_to(t_us *arr, t_ull v, t_us i)
{
	while (v)
	{
		arr[i] += v % 10000;
		v /= 10000;
		if (arr[i] / 10000)
		{
			v += arr[i] / 10000;
			arr[i] %= 10000;
		}
		++i;
	}
	return (arr);
}
