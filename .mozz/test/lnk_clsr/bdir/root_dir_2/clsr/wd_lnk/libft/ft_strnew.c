/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:03:34 by tvanessa          #+#    #+#             */
/*   Updated: 2019/10/12 03:32:27 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t		sc;
	char		*str;
	size_t		i;

	sc = sizeof(char);
	str = NULL;
	if ((size + 1) == 0 || !(str = (char*)malloc(sc * (size + sc))))
		return (NULL);
	i = 0;
	while (i < (size + sc))
		str[i++] = 0x0;
	return (str);
}
