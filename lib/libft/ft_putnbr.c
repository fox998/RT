/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:15:49 by afokin            #+#    #+#             */
/*   Updated: 2017/11/01 18:15:51 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	dtoc(unsigned int n)
{
	char c;

	if (n / 10 == 0)
	{
		c = n + '0';
		write(1, &c, 1);
		return ;
	}
	else
		dtoc(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}

void		ft_putnbr(int n)
{
	unsigned int num;

	if (n < 0)
	{
		num = -n;
		write(1, "-", 1);
	}
	else
		num = n;
	dtoc(num);
}
