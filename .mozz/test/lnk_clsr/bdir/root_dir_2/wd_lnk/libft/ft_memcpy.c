/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:31:23 by tvanessa          #+#    #+#             */
/*   Updated: 2019/09/14 18:52:38 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*r;
	char	*s;
	int		i;

	r = (char*)dst;
	s = (char*)src;
	i = -1;
	if (r || s)
		while (++i < (int)n)
			r[i] = s[i];
	return (dst);
}
