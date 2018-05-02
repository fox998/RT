/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 15:29:45 by afokin            #+#    #+#             */
/*   Updated: 2017/11/24 15:29:47 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_realloc(char *ptr, int len)
{
	char	*newptr;
	int		i;

	i = -1;
	if (!ptr)
		return ((char *)ft_memalloc(len));
	newptr = (char *)ft_memalloc(ft_strlen(ptr) + len);
	while (ptr[++i])
		newptr[i] = ptr[i];
	free(ptr);
	return (newptr);
}

static t_file	*init_fl(const int fd)
{
	t_file *tmp;

	if (!((tmp) = (t_file *)malloc(sizeof(t_file))))
		return (0);
	if (!((tmp)->buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (0);
	ft_bzero((tmp)->buf, BUFF_SIZE + 1);
	(tmp)->fd = fd;
	(tmp)->str_start = -1;
	(tmp)->next = NULL;
	return (tmp);
}

static int		read_nl(t_file *fl, char **line, int j, int len)
{
	if (fl->str_start != -1 && fl->buf[fl->str_start + 1] != '\0')
	{
		*line = ft_realloc(*line, BUFF_SIZE + 1);
		while (++(fl->str_start) < BUFF_SIZE)
			if (fl->buf[fl->str_start] == '\n' ||
				fl->buf[fl->str_start] == '\0')
				return (1);
			else
				(*line)[++j] = fl->buf[fl->str_start];
	}
	ft_bzero(fl->buf, BUFF_SIZE + 1);
	while ((len = read(fl->fd, fl->buf, BUFF_SIZE)) > 0)
	{
		*line = ft_realloc(*line, BUFF_SIZE + 1);
		fl->str_start = -1;
		while (++(fl->str_start) < len)
			if (fl->buf[fl->str_start] == '\n')
				return (1);
			else
				(*line)[++j] = fl->buf[fl->str_start];
		ft_bzero(fl->buf, BUFF_SIZE + 1);
	}
	if (!len && (*line))
		return (1);
	return (len);
}

int				get_next_line(const int fd, char **line)
{
	static t_file	*fl = NULL;
	t_file			*tmp;

	tmp = fl;
	if (!line || fd < 0)
		return (-1);
	*line = NULL;
	if (!fl)
	{
		fl = init_fl(fd);
		return (read_nl(fl, line, -1, -1));
	}
	while ((tmp)->next)
	{
		if (tmp->fd == fd)
			break ;
		(tmp) = (tmp)->next;
	}
	if ((tmp->fd != fd))
	{
		tmp->next = init_fl(fd);
		return (read_nl((tmp->next), line, -1, -1));
	}
	else
		return (read_nl((tmp), line, -1, -1));
}
