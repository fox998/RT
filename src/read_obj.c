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
#include "vector.h"
#include <stdlib.h>
#include <math.h>

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

void	read_vector_fild(void *fild_ptr, char *fild_name, int fd)
{
	char	**mas;
	char	*line;
	t_dvec3	*fild;
	int		l;

	(l = num_line(fd, &line)) < 0 ||
	ft_strncmp(fild_name, line, ft_strlen(fild_name)) != 0 ?
		(sintax_usage(l)) : *(line += ft_strlen(fild_name));
	mas = ft_strsplit(line, ',');
	fild = fild_ptr;
	mas[0] ? (*fild)[0] = (ft_atoi(mas[0])) : sintax_usage(l);
	mas[1] ? (*fild)[1] = (ft_atoi(mas[1])) : sintax_usage(l);
	mas[2] ? (*fild)[2] = (ft_atoi(mas[2])) : sintax_usage(l);
	free_mas(mas);
	free(line - ft_strlen(fild_name));
}

int	read_int_fild(char *fild_name, int base, int fd)
{
	char	*line;
	int		res;
	int		l;

	(l = num_line(fd, &line)) < 0 ||
	ft_strncmp(fild_name, line, ft_strlen(fild_name)) != 0 ?
		(sintax_usage(l)) : *(line += ft_strlen(fild_name));
	res = ft_atoi_base(line, base);
	free(line - ft_strlen(fild_name));
	return (res);
}

#include <stdio.h>

void		*read_cam(int fd)
{
	t_cam	*cam;

	cam = (t_cam *)malloc(sizeof(t_cam));
	read_vector_fild(&cam->pos, "\tpos => ", fd);
	read_vector_fild(&cam->dir, "\tdir => ", fd);
	cam->u[0] = 0;
	norm_vector(&cam->dir);
	if (cam->dir[0] == 0 && cam->dir[1] == 0)
	{
		cam->u[1] = 1;
		cam->u[2] = 0;
		vector_product(&cam->r, cam->dir, cam->u);
		norm_vector(&cam->r);
	}
	else
	{
		cam->u[1] = 0;
		cam->u[2] = 1;
		vector_product(&cam->r, cam->dir, cam->u);
		norm_vector(&cam->r);
		vector_product(&cam->u, cam->r, cam->dir);
		norm_vector(&cam->u);
	}
	return (cam);
}
