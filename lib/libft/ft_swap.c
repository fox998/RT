/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 17:56:08 by afokin            #+#    #+#             */
/*   Updated: 2017/11/05 17:56:10 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(void *p1, void *p2, size_t len)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	unsigned char	tmp;
	size_t			i;

	i = 0;
	ptr1 = (unsigned char *)p1;
	ptr2 = (unsigned char *)p2;
	while (++i <= len)
	{
		tmp = *ptr1;
		*ptr1 = *ptr2;
		*ptr2 = tmp;
		ptr1++;
		ptr2++;
	}
}
