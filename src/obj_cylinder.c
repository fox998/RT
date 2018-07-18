/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:00:13 by afokin            #+#    #+#             */
/*   Updated: 2018/05/03 17:00:15 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"
#include "vector.h"
#include <stdlib.h>
#include <math.h>

static void		dop(t_iparam *p, t_dvec3 *tmp, t_dvec3 eye, t_cylinder *c)
{
	get_vector(&p->v, eye, -1, p->i_point);
	get_vector(&tmp[0], p->i_point, -1, c->pos);
	get_vector(&tmp[0], c->pos, dot_product(c->dir, tmp[0]), c->dir);
	get_vector(&p->normal, p->i_point, -1, tmp[0]);
	norm_vector(&p->v);
	norm_vector(&p->normal);
	p->color = texture_mapping(p->txr, c->pos, p->i_point, CYLINDER_CORD, &c->dir[0]);
}

int				cylinder_intersect(void *data,
				t_dvec3 ray, t_dvec3 eye, t_iparam *p)
{
	t_dvec3		tmp[2];
	t_dvec3		dp;
	double		t;
	double		abc[4];
	t_cylinder	*c;

	c = data;
	get_vector(&tmp[0], ray, -1 * dot_product(c->dir, ray), c->dir);
	abc[0] = dot_product(tmp[0], tmp[0]);
	get_vector(&dp, eye, -1, c->pos);
	get_vector(&tmp[1], dp, -1 * dot_product(dp, c->dir), c->dir);
	abc[1] = 2.0 * dot_product(tmp[0], tmp[1]);
	abc[2] = dot_product(tmp[1], tmp[1]) - c->r * c->r;
	abc[3] = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if ((abc[3]) < 0 || (abc[0] == 0 && abc[1] == 0) ||
		((t = (-abc[1] - sqrt(abc[3])) / (2.0 * abc[0])) <= 0.00001 &&
		(t = (-abc[1] + sqrt(abc[3])) / (2.0 * abc[0])) <= 0.00001) ||
		(p && p->t > 0 && p->t <= t))
		return (0);
	if (!p)
		return (1);
	p->t = t;
	get_vector(&p->i_point, eye, p->t, ray);
	dop(p, &tmp[0], eye, c);
	return (1);
}

void			*read_cylinder(int fd)
{
	t_cylinder	*cylinder;
	t_obj_3d	*shape;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	read_vector_fild(&cylinder->pos, "\tpos => ", fd);
	read_vector_fild(&cylinder->dir, "\tdir => ", fd);
	norm_vector(&cylinder->dir);
	cylinder->r = fmax(1, read_int_fild("\tr => ", 10, fd));
	cylinder->color = read_int_fild("\tcolor => ", 16, fd);
	shape = (t_obj_3d *)malloc(sizeof(t_obj_3d));
	shape->data = cylinder;
	shape->intersect = &cylinder_intersect;
	return (shape);
}
