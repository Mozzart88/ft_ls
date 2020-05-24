/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:25:15 by tvanessa          #+#    #+#             */
/*   Updated: 2020/01/06 21:40:37 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	int		t;

	i = 0;
	t = 0;
	while (i < len)
	{
		if (src[i] && t == 0)
			dst[i] = src[i];
		else
			dst[i] = '\0';
		if (src[i] == '\0')
			t = 1;
		++i;
	}
	return (dst);
}
