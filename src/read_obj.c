/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 14:42:17 by afokin            #+#    #+#             */
/*   Updated: 2018/03/25 14:42:19 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"
#include "function.h"
#include <stdlib.h>

static void	free_mas(char **mas)
{
	char **tmp;

	tmp = mas;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(mas);
}

#include <stdio.h>

void		read_cam(int fd)
{
	char	*line;
	char	**mas;
	int		l;
	t_cam	*cam;

	ft_putendl("pos");
	(l = num_line(fd, &line)) < 0 || ft_strncmp("\tpos =>", line, 6) != 0 ?
		(sintax_usage(l)) : *(line += 6);
	cam = (t_cam *)malloc(sizeof(t_cam));
	mas = ft_strsplit(line, ',');
	mas[0] ? cam->pos[0] = (ft_atoi(mas[0])) : sintax_usage(l);
	mas[1] ? cam->pos[1] = (ft_atoi(mas[1])) : sintax_usage(l);
	mas[2] ? cam->pos[2] = (ft_atoi(mas[2])) : sintax_usage(l);
	free_mas(mas);
	(l = num_line(fd, &line)) < 0 || ft_strncmp("\trot =>", line, 6) != 0 ?
		sintax_usage(l) : *(line += 6);
	ft_putendl("rot");
	mas = ft_strsplit(line, ',');
	mas[0] ? cam->dir[0] = ft_atoi(mas[0]) : sintax_usage(l);
	mas[1] ? cam->dir[1] = ft_atoi(mas[1]) : sintax_usage(l);
	mas[2] ? cam->dir[2] = ft_atoi(mas[2]) : sintax_usage(l);
	free_mas(mas);
	printf("pos = %f, %f, %f\nrot = %f, %f, %f\n", cam->pos[0], cam->pos[1], cam->pos[2], cam->dir[0], cam->dir[1], cam->dir[2]);
}

void		read_win(int fd)
{
	fd = 0;
}

