/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 14:36:20 by afokin            #+#    #+#             */
/*   Updated: 2017/10/28 14:36:24 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char			*p;
	unsigned char	ch;
	int				i;

	p = (char *)s;
	ch = c;
	i = -1;
	while ((size_t)++i < n)
		if ((unsigned char)p[i] == ch)
			return (p + i);
	return (0);
}
