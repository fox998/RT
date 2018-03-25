/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:57:21 by afokin            #+#    #+#             */
/*   Updated: 2017/10/30 16:57:23 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	int		i;

	ptr = malloc(len + 1);
	if (!s || !ptr)
		return (0);
	i = 0;
	while ((size_t)i < len && (ptr[i] = s[start + i]))
		i++;
	ptr[i] = 0;
	return (ptr);
}
