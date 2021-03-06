/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 10:48:37 by afokin            #+#    #+#             */
/*   Updated: 2018/03/24 11:15:23 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"
#include "vector.h"
#include "libft.h"
#include <fcntl.h>

static t_read	*arr_init(t_read *arr, int arr_size)
{
	arr[0].name = "camera";
	arr[0].f = &read_cam;
	arr[1].name = "sphere";
	arr[1].f = &read_sphere;
	arr[2].name = "light";
	arr[2].f = &read_light;
	arr[3].name = "cylinder";
	arr[3].f = &read_cylinder;
	arr[4].name = "plane";
	arr[4].f = &read_plane;
	arr[5].name = "cone";
	arr[5].f = &read_cone;
	arr[6].name = "qudric";
	arr[6].f = &read_qudric;
	arr[7].name = "tore";
	arr[7].f = &read_tore;
	arr[arr_size].name = 0;
	return (arr);
}

static void		add_obj(t_window *wind, t_read *obj, int fd)
{
	t_obj_3d	*new_3d_obj;
	t_scene		*scn;
	t_light		*light;

	scn = wind->scn;
	if (ft_strncmp("cam", obj->name, 3) == 0)
	{
		wind->cam = obj->f(fd);
		get_vector(&wind->cam->u, wind->cam->u,
		wind->h / (double)wind->w - 1.0, wind->cam->u);
	}
	else if (ft_strncmp("lig", obj->name, 3) == 0)
	{
		light = obj->f(fd);
		light->next = scn->lit;
		scn->lit = light;
	}
	else
	{
		new_3d_obj = obj->f(fd);
		new_3d_obj->txr = wind->txr;
		ft_lstadd((t_list **)&scn->obj,
		ft_lstnew(new_3d_obj, sizeof(t_obj_3d)));
		free(new_3d_obj);
	}
}

static int		check_brackets(t_read *obj, int fd, t_window *wind)
{
	char	*line;
	int		l;

	if ((l = num_line(fd, &line)) < 0 || *line != '{')
		sintax_usage(l);
	free(line);
	add_obj(wind, obj, fd);
	if ((l = num_line(fd, &line)) < 0 || *line != '}')
		sintax_usage(l);
	free(line);
	return (0);
}

#include	<stdio.h>

void			read_scene(char *path, void *wind)
{
	int		fd;
	char	*line;
	int		i;
	int		l;
	t_read	arr[9];

	if ((fd = open(path, O_RDONLY)) < 0)
		usage('f');
	arr_init((t_read *)arr, 8);
	((t_window *)wind)->scn->lit = 0;
	((t_window *)wind)->cam = 0;
	while ((l = num_line(fd, &line)) > 0)
	{
		if (!*line)
		{
			free(line);
			continue ;
		}
		i = 0;
		while (arr[i].name && ft_strncmp(line,
		arr[i].name, ft_strlen(arr[i].name)))
			i++;
		arr[i].name ? check_brackets(&arr[i], fd, wind) : sintax_usage(l);
		free(line);
	}
}
