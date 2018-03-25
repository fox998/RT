/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 21:09:04 by afokin            #+#    #+#             */
/*   Updated: 2017/10/26 21:09:06 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*psrc;
	char	*pdst;
	int		i;

	psrc = (char *)src;
	pdst = (char *)dst;
	i = -1;
	while ((size_t)++i < n)
		pdst[i] = psrc[i];
	return (dst);
}
