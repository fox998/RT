/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 17:38:02 by afokin            #+#    #+#             */
/*   Updated: 2017/10/30 17:38:04 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	int		slen;
	int		i;
	char	*ptr;
	char	*mys;

	if (!s)
		return (0);
	slen = ft_strlen((char *)s);
	if (!(ptr = malloc(slen + 1)))
		return (0);
	i = 0;
	mys = (char *)s;
	while (*mys == ' ' || *mys == '\t' || *mys == '\n')
		mys++;
	while ((ptr[i] = mys[i]) && mys[i + 1])
		i++;
	while (ptr[i] == ' ' || ptr[i] == '\t' || ptr[i] == '\n')
		i--;
	ptr[i + 1] = 0;
	return (ptr);
}
