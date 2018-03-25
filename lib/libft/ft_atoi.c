/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 12:35:49 by afokin            #+#    #+#             */
/*   Updated: 2017/10/30 12:35:51 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	foo(unsigned long long res, int z)
{
	if (z < 0)
		if (res > 9223372036854775807)
			return (0);
		else
			return (-res);
	else if (res > 9223372036854775807)
		return (-1);
	else
		return (res);
}

int			ft_atoi(char *str)
{
	int					z;
	unsigned long long	res;

	z = 1;
	res = 0;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str < '0' || *str > '9')
	{
		if (*str != '-' && *str != '+')
			return (0);
		else if (*str == '-')
			z = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		res = res * 10 + *(++str - 1) - '0';
	return (foo(res, z));
}
