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

static int	check_brackets(void (*f)(int fd), int fd)
{
	char	*line;

	if (get_next_line(fd, &line) < 1 || *line != '{')
		usage('s');
	free(line);
	f(fd);
	
}

static int	check_obj(char *line)
{
	int		r;
	char	*stim;

	r = -1;
	stim  = ft_strtrim(line);
	!ft_strcmp(stim, "camera") ? r = 0 : 0;
	!ft_strcmp(stim, "window") ? r = 1 : 0;
	free(stim);
	return(r);
}

void		read_scene(char *path)
{
	int		fd;
	char	*line;
	int		i;
	int		(*fun[2])(int fd);


	if ((fd = open(path, O_RDONLY)) < 0)
		usage('f');
	fun[0] = &read_cam;
	fun[1] = &read_win;
	while (get_next_line(fd, line) > 0)
	{
		if (!*line)
		{
			free(line);
			continue ;
		}
		(i = check_obj(line)) > 0 ? fun[i](fd) : (usage('s'));
	}
}
