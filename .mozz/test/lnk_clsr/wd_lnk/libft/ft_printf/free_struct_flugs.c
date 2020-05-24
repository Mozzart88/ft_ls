/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct_flugs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:57:01 by gmentat           #+#    #+#             */
/*   Updated: 2020/01/07 14:32:53 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		free_struct_flugs(t_f_arg *struct_flugs)
{
	ft_strdel(&struct_flugs->yes);
	struct_flugs->yes = NULL;
	struct_flugs->width = NULL;
	struct_flugs->i_point = 0;
	struct_flugs->i_width = 0;
	struct_flugs->length = NULL;
	struct_flugs->point = NULL;
	struct_flugs->spase = NULL;
	struct_flugs->zero = NULL;
	struct_flugs->minus = NULL;
	struct_flugs->less_zero = NULL;
	struct_flugs->plus = NULL;
	struct_flugs->grill = NULL;
	struct_flugs->fl = NULL;
	struct_flugs->fll = NULL;
	struct_flugs->fh = NULL;
	struct_flugs->fhh = NULL;
	struct_flugs->temp = NULL;
	struct_flugs->j = NULL;
	struct_flugs->z = NULL;
	struct_flugs->t = NULL;
	struct_flugs->exeptions = 0;
}
