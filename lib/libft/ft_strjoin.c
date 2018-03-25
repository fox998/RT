/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 17:20:27 by afokin            #+#    #+#             */
/*   Updated: 2017/10/30 17:20:29 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1len;
	int		s2len;
	char	*ptr;
	int		i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	s1len = ft_strlen((char *)s1);
	s2len = ft_strlen((char *)s2);
	if (!(ptr = malloc(s1len + s2len + 1)))
		return (0);
	while ((ptr[i] = s1[i]))
		i++;
	i = 0;
	while ((ptr[s1len + i] = s2[i]))
		i++;
	return (ptr);
}
