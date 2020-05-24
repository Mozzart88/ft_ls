/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 22:20:46 by tvanessa          #+#    #+#             */
/*   Updated: 2019/09/19 12:29:32 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list **lst, t_list *new)
{
	if (lst && *lst && new)
	{
		if ((*lst)->next)
			ft_lstappend(&(*lst)->next, new);
		else
			(*lst)->next = new;
	}
}
