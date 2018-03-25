/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 14:11:28 by afokin            #+#    #+#             */
/*   Updated: 2017/10/29 14:11:30 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *big, char *little, size_t len)
{
	char	*tmpl;
	char	*tmpb;

	tmpl = little;
	if (*little == '\0')
		return (big);
	while (*big && len > 0)
		if (*big == *tmpl)
		{
			tmpb = big;
			while (*tmpl == *tmpb++ && *tmpl && len-- > 0)
				tmpl++;
			len += tmpb - big;
			if (*tmpl == '\0')
				return (big);
			tmpl = little;
			big++;
		}
		else
		{
			big++;
			len--;
		}
	return (0);
}
