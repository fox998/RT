/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 16:59:10 by afokin            #+#    #+#             */
/*   Updated: 2018/05/03 16:59:13 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"
#include "vector.h"
#include <math.h>
#include <stdlib.h>

int			plane_intersect(void *data, t_dvec3 ray, t_dvec3 e, t_iparam *p)
{
	t_plane		*plane;
	t_dvec3		ep;
	t_dvec3		i_p;
	double		t;
	double		vn;

	plane = data;
	if ((vn = (dot_product(ray, plane->n))) == 0.0)
		return (0);
	get_vector(&ep, plane->plane_point, -1, e);
	t = dot_product(ep, plane->n) / vn;
	get_vector(&i_p, e, t, ray);
	if (t <= 0.00001 || (p && p->t > 0 && p->t <= t))
		return (0);
	if (!p)
		return (1);
	get_vector(&p->i_point, e, t, ray);
	get_vector(&p->normal, plane->n, vn < 0 ? 0 : -2, plane->n);
	get_vector(&p->v, e, -1, p->i_point);
	norm_vector(&p->v);
	p->t = t;
	p->color =  texture_mapping(p, plane->plane_point, p->i_point, PLANE_CORD, plane->n);
	return (1);
}

void		*read_plane(int fd)
{
	t_obj_3d	*shape;
	t_plane		*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	read_vector_fild(&plane->n, "\tdir => ", fd);
	read_vector_fild(&plane->plane_point, "\tpos => ", fd);
	plane->color = read_int_fild("\tcolor => ", 16, fd);
	norm_vector(&plane->n);
	shape = (t_obj_3d *)malloc(sizeof(t_obj_3d));
	shape->data = plane;
	shape->intersect = &plane_intersect;
	return (shape);
}
