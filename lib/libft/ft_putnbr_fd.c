/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:46:03 by afokin            #+#    #+#             */
/*   Updated: 2017/11/01 18:46:06 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	dtoc(unsigned int n, int fd)
{
	char c;

	if (n / 10 == 0)
	{
		c = n + '0';
		write(fd, &c, 1);
		return ;
	}
	else
		dtoc(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}

void		ft_putnbr_fd(int n, int fd)
{
	unsigned int num;

	if (n < 0)
	{
		num = -n;
		write(fd, "-", 1);
	}
	else
		num = n;
	dtoc(num, fd);
}
