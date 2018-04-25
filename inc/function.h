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

/*
*	USAGE
*/
int			usage(char f);
int			str_usage(char *str);
int			sintax_usage(int line);
int			num_line(int fd, char **line);

/*
*	READ
*/
void		*read_cam(int fd);
void		*read_win(int fd);
void		*read_sphere(int fd);
void		*read_light(int fd);
void		*read_plane(int fd);
void		*read_cylinder(int fd);
void		*read_cone(int fd);
void		read_scene(char *path, void *wind);
void		get_scene(void *wind);
int			ft_atoi_base(const char *str, int str_base);
void		read_vector_fild(void *fild_ptr, char *fild_name, int fd);
int			read_int_fild(char *fild_name, int base, int fd);

/*
*	RENDER
*/
void		render(void *wind);

#endif
