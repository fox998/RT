/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:09:25 by afokin            #+#    #+#             */
/*   Updated: 2017/11/02 15:09:27 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	if (content && ptr && content_size)
	{
		ptr->next = 0;
		if ((ptr->content = malloc(content_size)))
			ptr->content_size = content_size;
		else
		{
			free(ptr);
			return (0);
		}
		ft_memcpy(ptr->content, content, content_size);
	}
	else if (ptr)
	{
		ptr->content = 0;
		ptr->content_size = 0;
		ptr->next = 0;
	}
	return (ptr);
}
