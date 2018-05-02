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

/*
******* VECTOR ****************************************************************
*/

typedef double			t_dvec3[3];

typedef int				t_ivec3[3];

/*
******* HELP STRUCT ***********************************************************
*/

typedef struct			s_read
{
	char		*name;
	void		*(*f)(int fd);
}						t_read;

typedef struct			s_intersect_param
{
	t_dvec3			i_point;
	t_dvec3			normal;
	t_dvec3			v;
	double			t;
	unsigned int	color;
}						t_iparam;

typedef struct			s_shading
{
	t_dvec3			l;
	t_dvec3			h;
	double			h_dot_n;
	double			phong;
	double			lambert;
}						t_shading;

/*
******* OBJECT STRUCT *********************************************************
*/

typedef	struct			s_obj_3d
{
	void		*data;
	int			(*intersect)(void *data, t_dvec3 ray, t_dvec3 e, t_iparam *param);
}						t_obj_3d;

typedef struct			s_sphere
{
	double			r;
	t_dvec3			center;
	unsigned int	color;
}						t_sphere;

typedef struct			s_light
{
	t_dvec3			dir;
	double			intensity;
	struct s_light	*next;
}						t_light;

typedef struct			s_plane
{
	t_dvec3			n;
	t_dvec3			plane_point;
	unsigned int	color;
}						t_plane;

typedef	struct			s_cylinder
{
	t_dvec3			dir;
	t_dvec3			pos;
	unsigned int	r;
	unsigned int	color;
}						t_cylinder;

typedef	struct			s_cone
{
	t_dvec3			dir;
	t_dvec3			pos;
	unsigned int	a;
	unsigned int	color;
	double			sin_a;
	double			cos_a;
}						t_cone;

/*
******* MANAGERS STRUCT *******************************************************
*/

typedef struct			s_color
{
	unsigned int	r:8;
	unsigned int	g:8;
	unsigned int	b:8;
	unsigned int	a:8;
}						t_color;

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
	t_dvec3		u;
	t_dvec3		r;
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
	t_cam		*cam;
	void		*ren;
	t_scene		*scn;
	int			w;
	int			h;
}						t_window;

#endif
