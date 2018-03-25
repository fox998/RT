/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 15:11:27 by afokin            #+#    #+#             */
/*   Updated: 2017/10/29 15:11:45 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *st1, const char *st2, size_t len)
{
	unsigned char	*s1;
	unsigned char	*s2;
	int				siz;

	s1 = (unsigned char *)st1;
	s2 = (unsigned char *)st2;
	siz = 0;
	if (len == 0)
		return (0);
	while (*s1 == *s2 && *s2 && (size_t)++siz < len)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
