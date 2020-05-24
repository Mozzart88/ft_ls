/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revers_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmentat <gmentat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 23:11:04 by gmentat           #+#    #+#             */
/*   Updated: 2019/12/20 18:02:05 by gmentat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*revers_str(char *str)
{
	int		j;
	int		i;
	char	*buff;

	j = 0;
	i = ft_strlen(str) - 1;
	buff = ft_strnew(i);
	while (j < ((int)ft_strlen(str)))
	{
		buff[j] = str[i];
		i--;
		j++;
	}
	return (buff);
}
