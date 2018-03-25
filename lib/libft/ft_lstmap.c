/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 16:41:00 by afokin            #+#    #+#             */
/*   Updated: 2017/11/02 16:41:01 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ptr;
	t_list	*tmp;
	t_list	*rtn;

	rtn = 0;
	while (lst && !rtn)
	{
		if ((tmp = f(lst)))
			rtn = ft_lstnew(tmp->content, tmp->content_size);
		lst = lst->next;
	}
	ptr = rtn;
	while (lst)
	{
		if ((tmp = f(lst)))
		{
			ptr->next = ft_lstnew(tmp->content, tmp->content_size);
			ptr = ptr->next;
		}
		lst = lst->next;
	}
	return (rtn);
}
