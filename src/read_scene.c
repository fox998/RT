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

#include "../inc/struct.h"
#include "../inc/function.h"
#include "../lib/libft/libft.h"
#include <fcntl.h>

static int	check_obj(char *line)
{
	int		r;
	char	*stim;

	r = 0;
	stim  = ft_strtrim(line);
	!ft_strcmp(stim, "camera") ? (r = 1 && read_cam()) : 0;
	free(stim);
	return(r);
}

void		read_scene(char *path, t_window *wind)
{
	int		fd;
	char	*line;


	if ((fd = open(path, O_RDONLY)) < 0)
		usage('f');
	while (get_next_line(fd, line) > 0)
	{
		
	}
}
