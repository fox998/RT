/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 14:26:28 by afokin            #+#    #+#             */
/*   Updated: 2017/10/29 14:26:30 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *st1, const char *st2)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)st1;
	s2 = (unsigned char *)st2;
	while (*s1 == *s2 && *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
