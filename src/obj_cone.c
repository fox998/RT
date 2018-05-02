/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 19:03:26 by afokin            #+#    #+#             */
/*   Updated: 2018/05/02 19:03:29 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"
#include "vector.h"
#include <math.h>
#include <stdlib.h>

int			cone_intersect(void *data, t_dvec3 ray, t_dvec3 eye, t_iparam *p)
{
	t_cone		*c;
	t_dvec3		tmp[3];
	double		abc[4];
	double		dot[2];
	double		t;

	c = data;
	dot[0] = dot_product(ray, c->dir);
	get_vector(&tmp[0], ray, -dot[0], c->dir);
	abc[0] = c->cos_a * dot_product(tmp[0], tmp[0]) - c->sin_a * dot[0] * dot[0];
	get_vector(&tmp[2], eye, -1, c->pos);
	dot[1] = dot_product(tmp[2], c->dir);
	get_vector(&tmp[1], tmp[2], -dot[1], c->dir);
	abc[1] = 2 * (c->cos_a * dot_product(tmp[0], tmp[1]) - c->sin_a * dot[0] * dot[1]);
	abc[2] = c->cos_a * dot_product(tmp[1], tmp[1]) - c->sin_a * dot[1] * dot[1];
	abc[3] = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (abc[3] < 0 || 
		(t = (-abc[1] - sqrt(abc[3])) / (2.0 * abc[0])) <= 0.00001 ||
		(p && p->t > 0 && p->t <= t))
		return (0);
	if (!p)
		return (1);
	p->t = t;
	get_vector(&p->i_point, eye, p->t, ray);
	get_vector(&p->v, eye, -1, p->i_point);
	get_vector(&tmp[0], p->i_point, -1, c->pos);
	get_vector(&tmp[0], c->pos, dot_product(c->dir, tmp[0]), c->dir);
	get_vector(&p->normal, p->i_point, -1, tmp[0]);
	norm_vector(&p->v);
	norm_vector(&p->normal);
	p->color = c->color;
	return (1);
}

void		*read_cone(int fd)
{
	t_cone		*cone;
	t_obj_3d	*shape;

	cone = (t_cone *)malloc(sizeof(t_cone));
	read_vector_fild(&cone->pos, "\tpos => ", fd);
	read_vector_fild(&cone->dir, "\tdir => ", fd);
	norm_vector(&cone->dir);
	cone->a = fmin(45, fmax(10, read_int_fild("\ta => ", 10, fd)));
	cone->color = read_int_fild("\tcolor => ", 16, fd);
	cone->sin_a = pow(sin(cone->a * 3.14 / 180.0), 2);
	cone->cos_a = pow(cos(cone->a * 3.14 / 180.0), 2);
	shape = (t_obj_3d *)malloc(sizeof(t_obj_3d));
	shape->data = cone;
	shape->intersect = &cone_intersect;
	return(shape);
}
