/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 12:42:44 by afokin            #+#    #+#             */
/*   Updated: 2017/10/29 12:42:48 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *big, char *little)
{
	char	*tmpl;
	char	*tmpb;

	tmpl = little;
	if (*little == '\0')
		return (big);
	while (*big)
		if (*big == *tmpl)
		{
			tmpb = big;
			while (*tmpl == *tmpb++ && *tmpl)
				tmpl++;
			if (*tmpl == '\0')
				return (big);
			tmpl = little;
			big++;
		}
		else
			big++;
	return (0);
}
