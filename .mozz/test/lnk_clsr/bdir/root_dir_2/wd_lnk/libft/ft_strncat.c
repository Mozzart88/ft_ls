/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 20:37:24 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/17 16:29:03 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	if ((n + 1) == 0 || !(str = (char*)malloc(sizeof(char) * n + 1)))
		return (NULL);
	while (i < n)
	{
		str[i] = *s2;
		s2++;
		i++;
	}
	str[i] = '\0';
	s1 = ft_strcat(s1, str);
	ft_strdel(&str);
	return (s1);
}
