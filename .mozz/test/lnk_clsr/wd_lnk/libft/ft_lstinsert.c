/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 22:03:03 by tvanessa          #+#    #+#             */
/*   Updated: 2019/09/19 12:28:48 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstinsert(t_list **lst, t_list *new, size_t n)
{
	if (lst && *lst && new)
	{
		if ((*lst)->next && n > 0)
			ft_lstinsert(&(*lst)->next, new, n - 1);
		else if (!(*lst)->next && n > 0)
			return ;
		else
		{
			new->next = (*lst)->next;
			*lst = new;
		}
	}
}
