/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 19:55:49 by tvanessa          #+#    #+#             */
/*   Updated: 2019/09/19 13:05:22 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*l;

	if (!alst || !*alst || !del)
		return ;
	del((*alst)->content, (*alst)->content_size);
	l = (*alst)->next;
	free(*alst);
	*alst = NULL;
}
