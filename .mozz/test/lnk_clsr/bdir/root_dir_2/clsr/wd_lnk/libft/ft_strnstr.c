/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:23:19 by tvanessa          #+#    #+#             */
/*   Updated: 2019/09/05 19:46:45 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char		h[len];
	char		*res;
	size_t		i;

	i = 0;
	while (i < len)
	{
		h[i] = haystack[i];
		i++;
	}
	h[i] = '\0';
	res = ft_strstr(h, needle);
	if (res)
		res = ft_strstr(haystack, res);
	return (res);
}
