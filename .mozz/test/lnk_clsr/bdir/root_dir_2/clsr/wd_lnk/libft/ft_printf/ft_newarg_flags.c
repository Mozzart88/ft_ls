/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newarg_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 20:49:42 by gmentat           #+#    #+#             */
/*   Updated: 2020/01/06 19:55:19 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_f_arg		*ft_newarg_flags_helper(t_f_arg *fes)
{
	fes->width = NULL;
	fes->i_point = 0;
	fes->i_width = 0;
	fes->length = NULL;
	fes->point = NULL;
	fes->spase = NULL;
	fes->zero = NULL;
	fes->minus = NULL;
	fes->less_zero = NULL;
	fes->plus = NULL;
	fes->grill = NULL;
	fes->fl = NULL;
	fes->fll = NULL;
	fes->fh = NULL;
	fes->fhh = NULL;
	fes->temp = NULL;
	fes->yes = NULL;
	fes->j = NULL;
	fes->z = NULL;
	fes->t = NULL;
	fes->exeptions = 0;
	return (fes);
}

t_f_arg		*ft_newarg_flags(void)
{
	t_f_arg			*fes;

	if (!(fes = (t_f_arg*)malloc(sizeof(t_f_arg))))
		return (NULL);
	return (ft_newarg_flags_helper(fes));
}
