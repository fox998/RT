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
#include <stdlib.h>

void		read_cam(int fd)
{
	char	*line;
	char	**mas;
	int		i;
	t_cam	*cam;

	get_next_line(fd, &line) < 1 || ft_strncmp("pos =>", line, 6) != 0 ?
		usage('s') : line += 6;
	cam = (t_cam *)malloc(sizeof(t_cam));
	mas = ft_strsplit(line, ',');
	mas[0] ? cam->pos[0] = ft_atoi(mas[0]) && free(mas[0]) : usage('s');
	mas[1] ? cam->pos[1] = ft_atoi(mas[1]) && free(mas[1]) : usage('s');
	mas[2] ? cam->pos[2] = ft_atoi(mas[2]) && free(mas[2]) : usage('s');
	free(mas);
	get_next_line(fd, &line) < 1 || ft_strncmp("dir =>", line, 6) != 0 ?
		usage('s') : line += 6;
	mas = ft_strsplit(line, ',');
	mas[0] ? cam->pos[0] = ft_atoi(mas[0]) && free(mas[0]) : usage('s');
	mas[1] ? cam->pos[1] = ft_atoi(mas[1]) && free(mas[1]) : usage('s');
	mas[2] ? cam->pos[2] = ft_atoi(mas[2]) && free(mas[2]) : usage('s');
	free(mas);
}

void		read_win(int fd)
{

}

