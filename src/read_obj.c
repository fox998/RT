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

static void	read_vector_fild(t_dvec3 *fild, char *fild_name, int fd)
{
	char	**mas;
	char	*line;

	(l = num_line(fd, &line)) < 0 ||
	ft_strncmp(fild_name, line, ft_strlen(fild_name)) != 0 ?
		(sintax_usage(l)) : *(line += ft_strlen(fild_name));
	mas = ft_strsplit(line, ',');
	mas[0] ? (*pos)[0] = (ft_atoi(mas[0])) : sintax_usage(l);
	mas[1] ? (*pos)[1] = (ft_atoi(mas[1])) : sintax_usage(l);
	mas[2] ? (*pos)[2] = (ft_atoi(mas[2])) : sintax_usage(l);
	free_mas(mas);
	free(line);
}

void		read_cam(int fd)
{
	t_cam	*cam;

	cam = (t_cam *)malloc(sizeof(t_cam));
	read_vector_fild(&cam->pos, "\tpos => ", fd);
	read_vector_fild($cam->dir, "\tdir => ", fd);
}

void		read_win(int fd)
{
	fd = 0;
}

void		read_sphere(int fd)
{
	t_sphape	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	read_vector_fild(&sphere->center, "\tpos => ", fd);
	
}

