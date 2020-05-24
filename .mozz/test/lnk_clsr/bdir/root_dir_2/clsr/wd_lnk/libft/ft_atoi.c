/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:35:49 by tvanessa          #+#    #+#             */
/*   Updated: 2020/01/06 22:16:38 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int i;
	int min;
	int result;

	i = 0;
	min = 1;
	result = 0;
	while (str[i] == 9 || str[i] == 10 || str[i] == 13 || str[i] == 11
			|| str[i] == 12 || str[i] == 32)
		i++;
	if (str[i] == 45)
		min = -1;
	if (str[i] == 45 || str[i] == 43)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
		result = (result * 10) + (str[i++] - 48);
	return (result *= min);
}
