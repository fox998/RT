/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:59:27 by afokin            #+#    #+#             */
/*   Updated: 2018/05/03 17:59:29 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "libft.h"

static void		*lst_to_arr(t_list *lst)
{
	void	**arr;
	t_list	*tmp;
	int		size;
	int		i;

	size = 0;
	tmp = lst;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	arr = malloc(sizeof(t_obj_3d *) * (size + 1));
	i = -1;
	while (lst)
	{
		arr[++i] = lst->content;
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	arr[i + 1] = NULL;
	return (arr);
}

void			get_scene(void *window)
{
	t_scene		*scn;

	scn = ((t_window *)window)->scn;
	scn->obj = lst_to_arr(scn->obj);
}
