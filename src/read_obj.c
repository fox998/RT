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
	int		l;

	(l = num_line(fd, &line)) < 0 ||
	ft_strncmp(fild_name, line, ft_strlen(fild_name)) != 0 ?
		(sintax_usage(l)) : *(line += ft_strlen(fild_name));
	mas = ft_strsplit(line, ',');
	mas[0] ? (*fild)[0] = (ft_atoi(mas[0])) : sintax_usage(l);
	mas[1] ? (*fild)[1] = (ft_atoi(mas[1])) : sintax_usage(l);
	mas[2] ? (*fild)[2] = (ft_atoi(mas[2])) : sintax_usage(l);
	free_mas(mas);
	free(line - ft_strlen(fild_name));
}

static int	read_int_fild(char *fild_name, int base, int fd)
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

void		*read_cam(int fd)
{
	t_cam	*cam;

	cam = (t_cam *)malloc(sizeof(t_cam));
	read_vector_fild(&cam->pos, "\tpos => ", fd);
	read_vector_fild(&cam->dir, "\tdir => ", fd);
	return (cam);
}

// void		*read_win(int fd)
// {
// 	fd = 0;
// 	return (0);
// }

void		*read_sphere(int fd)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	read_vector_fild(&sphere->center, "\tcenter => ", fd);
	sphere->r = read_int_fild("\tr => ", 10, fd);
	sphere->color = read_int_fild("\tcolor => ", 16, fd);
	return (sphere);
}

