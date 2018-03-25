/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:09:04 by afokin            #+#    #+#             */
/*   Updated: 2017/11/01 16:09:06 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	dtoc(char **s, unsigned int n)
{
	if (n / 10 == 0)
	{
		**s = n + '0';
		return ;
	}
	else
		dtoc(s, n / 10);
	(*s)++;
	**s = n % 10 + '0';
}

char		*ft_itoa(int n)
{
	char		*ptr;
	char		*p;
	unsigned	num;

	if (!(ptr = malloc(sizeof(char) * 13)))
		return (0);
	ptr[12] = 0;
	if (n < 0)
	{
		*(ptr) = '-';
		p = ptr++;
		num = -n;
		dtoc(&(ptr), num);
	}
	else
	{
		num = n;
		p = ptr;
		dtoc(&ptr, num);
	}
	*(++ptr) = 0;
	return (p);
}
