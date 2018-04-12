/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 17:00:19 by afokin            #+#    #+#             */
/*   Updated: 2018/03/26 17:00:21 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

int		num_line(int fd, char **line)
{
	static int num = 0;
	
	if (get_next_line(fd, line) < 1)
		return (-1);
	if (*line)
	num++;
	return (num);
}
