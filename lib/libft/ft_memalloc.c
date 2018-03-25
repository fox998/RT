/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:26:54 by afokin            #+#    #+#             */
/*   Updated: 2017/10/30 14:26:56 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*ptr;
	int		i;

	i = -1;
	ptr = malloc(size);
	if (ptr == 0)
		return (0);
	while ((size_t)++i < size)
		((char *)ptr)[i] = 0;
	return (ptr);
}
