/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:26:09 by tvanessa          #+#    #+#             */
/*   Updated: 2019/10/01 18:29:53 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"

static t_list	*ft_lstget(t_list **alst, int fd)
{
	t_list	*lst;

	if (!alst)
		return (NULL);
	if (!*alst)
	{
		if (!(*alst = ft_lstnew(NULL, 0)))
			return (NULL);
		(*alst)->content_size = fd;
		if (!((*alst)->content = ft_strnew(1)))
			return (ft_free((void**)&(*alst)));
		return (*alst);
	}
	lst = *alst;
	while (lst->next && (int)lst->content_size != fd)
		lst = lst->next;
	if ((int)lst->content_size == fd)
		return (lst);
	if (!(lst->next = ft_lstnew(NULL, 0)))
		return (NULL);
	lst = lst->next;
	lst->content_size = fd;
	if (!(lst->content = ft_strnew(1)))
		return (ft_free((void**)&lst));
	return (lst);
}

static ssize_t	ft_get_line(int fd, char **line)
{
	ssize_t		ret;
	char		*tmp;
	char		buf[BUFF_SIZE + 1];

	tmp = NULL;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = 0x0;
		tmp = *line;
		if (!(*line = ft_strjoin(tmp, buf)))
			return (-1);
		ft_memdel((void**)&tmp);
		if (ft_strchr(buf, 0x0a))
			break ;
	}
	return (ret);
}

static int		ft_strcpy_m(char **line, char *content)
{
	char	*c;
	size_t	l;

	c = NULL;
	if ((c = ft_strchr(content, 0x0a)))
		if ((*line = ft_strnew((c - content))))
			if ((ft_memcpy(*line, content, (c - content))))
				return ((c - content));
	if ((l = ft_strlen(content)))
		if ((*line = ft_strnew(l)))
			if ((ft_memcpy(*line, content, l)))
				return (l);
	return (0);
}

static void		ft_lstrm_by_size(t_list **alst, size_t size)
{
	t_list *lst;
	t_list *plst;

	lst = *alst;
	plst = *alst;
	if (lst->content_size == size)
		*alst = lst->next;
	else
		while (lst->next)
		{
			plst = lst;
			lst = lst->next;
			if (lst->content_size == size)
				break ;
		}
	plst->next = lst->next;
	free(lst->content);
	lst->content = NULL;
	free(lst);
	lst = NULL;
}

int				get_next_line(int fd, char **line)
{
	int				ret;
	char			*tmp;
	static t_list	*flst;
	t_list			*cfd;

	if (fd <= -1 || !line || !(cfd = ft_lstget(&flst, fd)))
		return (-1);
	tmp = cfd->content;
	ret = ft_get_line(fd, &tmp);
	cfd->content = tmp;
	if (ret <= 0 && (!tmp || !*tmp))
	{
		ft_lstrm_by_size(&flst, fd);
		return (ret);
	}
	ret = ft_strcpy_m(line, cfd->content);
	tmp = cfd->content;
	if (tmp[ret] != '\0')
	{
		cfd->content = ft_strdup(&(tmp)[ret + 1]);
		ft_memdel((void**)&tmp);
	}
	else
		tmp[0] = 0x0;
	return (1);
}
