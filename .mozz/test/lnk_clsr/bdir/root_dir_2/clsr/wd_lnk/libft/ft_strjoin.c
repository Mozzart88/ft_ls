/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:46:04 by tvanessa          #+#    #+#             */
/*   Updated: 2019/09/11 20:08:35 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	size_t	l1;
	size_t	l2;
	size_t	i;

	r = NULL;
	if (!s1 || !s2)
		return (r);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	i = 0;
	if ((r = ft_strnew(l1 + l2)))
		while (i < l1 + l2)
		{
			if (i < l1)
				r[i] = s1[i];
			else
				r[i] = s2[i - l1];
			++i;
		}
	return (r);
}
