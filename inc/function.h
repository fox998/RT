/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 13:10:29 by afokin            #+#    #+#             */
/*   Updated: 2018/03/25 13:10:32 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

int			usage(char f);
int			sintax_usage(int line);
int			num_line(int fd, char **line);
void		*read_cam(int fd);
void		*read_win(int fd);
void		*read_sphere(int fd);
void		read_scene(char *path, t_window *wind);
int			ft_atoi_base(const char *str, int str_base);

#endif
