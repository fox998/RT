/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 22:32:35 by afokin            #+#    #+#             */
/*   Updated: 2017/10/26 22:32:36 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char	*psrc;
	char	*pdst;
	int		i;

	pdst = (char *)dst;
	psrc = (char *)src;
	i = -1;
	while ((size_t)++i < n)
	{
		pdst[i] = psrc[i];
		if (pdst[i] == c)
			return (pdst + i + 1);
	}
	return (0);
}
