/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:56:47 by tvanessa          #+#    #+#             */
/*   Updated: 2019/09/10 20:26:50 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*r;
	unsigned char		*s;
	unsigned char		*cc;

	i = 0;
	r = (unsigned char*)dst;
	s = (unsigned char*)src;
	if ((cc = ft_memchr(src, c, n)))
	{
		ft_memcpy(dst, src, (size_t)(cc - s + 1));
		return ((r + (size_t)(cc - s + 1)));
	}
	else
		ft_memcpy(dst, src, n);
	return (NULL);
}
