/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 16:08:28 by afokin            #+#    #+#             */
/*   Updated: 2017/11/02 16:08:30 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *ptr;
	t_list *tmp;

	if (!alst)
		return ;
	ptr = *alst;
	while (ptr)
	{
		del(ptr->content, ptr->content_size);
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
	*alst = 0;
}
