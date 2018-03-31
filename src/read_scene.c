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
#include "libft.h"
#include <fcntl.h>

static t_read	*arr_init()
{
	int		arr_size;
	t_read	*arr;

	arr_size = 2;
	arr = (t_read *)malloc(sizeof(t_read) * (arr_size + 1));
	arr[0].name = "camera";
	arr[0].f = &read_cam;
	arr[1].name = "sphere";
	arr[1].f = &read_sphere;
	arr[arr_size].name = 0;
	return (arr);
}

static int		check_brackets(t_read obj, int fd, t_window *wind)
{
	char	*line;
	int		l;

	if ((l = num_line(fd, &line)) < 0 || *line != '{')
		sintax_usage(l);
	free(line);
	fr_strncmp("cam", obj.name, 3) == 0 ? wind.cam = obj.f(fd) : ;
	if ((l = num_line(fd, &line)) < 0 || *line != '}')
		sintax_usage(l);
	free(line);
	return (0);
}

void		read_scene(char *path, t_window *wind)
{
	int		fd;
	char	*line;
	int		i;
	int		l;
	t_read	*arr;

	if ((fd = open(path, O_RDONLY)) < 0)
		usage('f');
	arr = arr_init();
	while ((l = num_line(fd, &line)) > 0)
	{
		if (!*line)
		{
			free(line);
			continue ;
		}
		i = 0;
		while (arr[i].name && ft_strncmp(line, arr[i].name, ft_strlen(arr[i].name)))
			i++;
		arr[i].name ? check_brackets(arr[i], fd, wind) : sintax_usage(l);
	}
}
