/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointers_stor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 04:53:34 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/09 05:19:31 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>

int main()
{
	unsigned long long		a;
	char	**b;
	char	*s;
	char	**s1;

	s = "a";
	b = &s;
	a = (unsigned long long)b;
	s1 = (char**)a;
	// printf("s\t=\t%#010x\n", s);
	printf("&s\t=\t%p\n", &s);
	printf("b\t=\t%p\n", b);
	printf("a\t=\t%#010llx\n", a);
	printf("s1\t=\t%p\n", s1);
	return (0);
}