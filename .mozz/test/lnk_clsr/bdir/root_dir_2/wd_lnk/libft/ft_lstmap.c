/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 21:44:31 by tvanessa          #+#    #+#             */
/*   Updated: 2019/09/19 12:21:29 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*l;

	l = NULL;
	if (!lst || !f || !(l = f(lst)))
		return (NULL);
	if (lst->next)
		if (!(l->next = ft_lstmap(lst->next, f)))
		{
			free(l);
			l = NULL;
			return (NULL);
		}
	return (l);
}
