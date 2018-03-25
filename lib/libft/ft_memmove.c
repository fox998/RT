/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 21:59:13 by afokin            #+#    #+#             */
/*   Updated: 2017/10/26 21:59:36 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*pdst;
	char		*psrc;
	int			i;

	pdst = (char *)dst;
	psrc = (char *)src;
	if (dst - src < 0)
	{
		i = -1;
		while (++i < (int)len)
			pdst[i] = psrc[i];
	}
	else if (src != dst)
	{
		i = len;
		while (--i > -1)
			pdst[i] = psrc[i];
	}
	return (dst);
}
