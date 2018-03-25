/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:12:14 by afokin            #+#    #+#             */
/*   Updated: 2017/10/28 16:12:15 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i])
		i++;
	tmp = (char *)malloc(i + 1);
	if (!tmp)
		return (0);
	i = 0;
	while ((tmp[i] = str[i]))
		i++;
	return (tmp);
}
