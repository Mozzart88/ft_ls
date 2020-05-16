/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointers_stor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 04:53:34 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/16 13:35:09 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>

int main()
{
	// void		*a;
	// char	**b;
	// char	*s;
	// char	**s1;
	// // void	*arr[10];

	// s = "a";
	// b = &s;
	// a = b;
	// s1 = (char**)a;
	// printf("s\t=\t%#010x\n", s);
	// printf("&s\t=\t%p\n", &s);
	// printf("b\t=\t%p\n", b);
	// printf("a\t=\t%p\n", a);
	// printf("s1\t=\t%p\n", s1);
	// printf("s1\t=\t%s\n", *s1);
	printf("s1\t=\t%lu\n", sizeof(void));
	printf("s1\t=\t%lu\n", sizeof(void*));
	printf("s1\t=\t%lu\n", sizeof(void**));
	printf("s1\t=\t%lu\n", sizeof(char**));
	return (0);
}