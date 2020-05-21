/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 21:35:04 by mozzart           #+#    #+#             */
/*   Updated: 2020/05/21 21:57:15 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(void)
{
	printf("t_stat = %lu\n", sizeof(t_stat));
	printf("t_stat* = %lu\n", sizeof(t_stat*));
	printf("t_rec = %lu\n", sizeof(t_rec));
	printf("t_rec* = %lu\n", sizeof(t_rec*));
	printf("t_vect = %lu\n", sizeof(t_vect));
	printf("t_vect* = %lu\n", sizeof(t_vect*));
	printf("t_maxvallen = %lu\n", sizeof(t_maxvallen));
	printf("t_maxvallen* = %lu\n", sizeof(t_maxvallen*));
	printf("t_datetime = %lu\n", sizeof(t_datetime));
	printf("t_datetime* = %lu\n", sizeof(t_datetime*));
	printf("acl_t = %lu\n", sizeof(acl_t));
	printf("acl_t* = %lu\n", sizeof(acl_t*));
	printf("t_dir = %lu\n", sizeof(t_dir));
	printf("t_dir* = %lu\n", sizeof(t_dir*));
	return (0);
}