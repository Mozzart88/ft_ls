/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:30:56 by tvanessa          #+#    #+#             */
/*   Updated: 2019/09/19 13:43:16 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char *s, char c)
{
	size_t	l;
	size_t	i;

	l = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == '\0' || s[i + 1] == c))
			++l;
		++i;
	}
	return (l);
}

static char		**ft_soft_split(char *st, char c, char **r)
{
	size_t	l;
	int		i;

	i = 0;
	l = 0;
	while (*st)
	{
		if (*st != c)
			++i;
		if (*st != c && (*(st + 1) == c || *(st + 1) == '\0'))
		{
			if (!(*r = ft_strsub((st + 1) - i, 0, i)))
				return (NULL);
			else
				break ;
			++l;
			i = 0;
		}
		++st;
	}
	if (*st)
		if (!(ft_soft_split(st + 1, c, r + 1)))
			ft_free((void**)&r);
	return (r);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	l;
	char	**r;
	char	*st;

	if (!s)
		return (NULL);
	i = 0;
	r = NULL;
	if (!(st = ft_strdup(s)))
		return (NULL);
	while (*st == c)
		++st;
	l = ft_strlen(st);
	if (l)
		while (st[--l] == c && (int)l >= 0)
			;
	st = ft_strsub(st, 0, ++l);
	l = ft_count_words(st, c);
	if (!(r = (char**)malloc(sizeof(char*) * (l + sizeof(char*)))))
		return (NULL);
	if (!(r = ft_soft_split(st, c, r)))
		return (ft_free((void**)&r));
	r[l] = NULL;
	return (r);
}
