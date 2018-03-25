/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 13:11:03 by afokin            #+#    #+#             */
/*   Updated: 2018/03/25 13:11:06 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../lib/libft/libft.h"
#include	<stdlib.h>

void	usage(char f)
{
	f == 'f' ? ft_putendl("Usage: ./RTv1 scene_file") : 0;
	f == 's' ? ft_putendl("Error: Invalid file format") : 0;
	exit(0);
}
