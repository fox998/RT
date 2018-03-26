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
	int		l;

	if ((l = num_line(fd, &line)) < 0 || *line != '{')
		sintax_usage(l);
	free(line);
	f(fd);
	if ((l = num_line(fd, &line)) < 0 || *line != '}')
		sintax_usage(l);
	free(line);
	return (0);
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
	int		l;
	void	(*fun[2])(int fd);


	if ((fd = open(path, O_RDONLY)) < 0)
		usage('f');
	fun[0] = &read_cam;
	fun[1] = &read_win;
	while ((l = num_line(fd, &line)) > 0)
	{
		if (!*line)
		{
			free(line);
			continue ;
		}
		ft_putendl(line);
		ft_putendl("--");
		(i = check_obj(line)) < 0 ?  (sintax_usage(l)) : check_brackets(fun[i], fd);
	}
	ft_putendl("***");
}
