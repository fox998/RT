/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 12:32:49 by afokin            #+#    #+#             */
/*   Updated: 2018/03/25 12:32:51 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef double			t_dvec3[3];

typedef int				t_ivec3[3];

typedef struct			s_read
{
	char		*name;
	void		*(*f)(int fd);
}						t_read;

typedef	struct			s_obj_3d
{
	void		*data;
	int			(*check)(void *data);
}						t_obj_3d;

typedef struct			s_sphere
{
	double			r;
	t_dvec3			center;
	unsigned int	color;
}						t_sphere;

typedef struct			s_scene
{
	void		*obj;
	void		*lit;
	void		*cam;
}						t_scene;

typedef	struct			s_cam
{
	t_dvec3		pos;
	t_dvec3		dir;
	t_dvec3		plane;
}						t_cam;

typedef struct			s_img
{
	void		*img_ptr;
	char		*data;
	int			bit_pix;
	int			byte_pix;
	int			line_size;
	int			endian;
	int			w;
	int			h;
}						t_img;

typedef struct			s_window
{
	void		*win;
	void		*cam;
	void		*ren;
	void		*lst_obg;
	void		*lst_lit;
	void		*scn;
	int			w;
	int			h;
}						t_window;

#endif
