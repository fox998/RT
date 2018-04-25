
#include "struct.h"
#include "function.h"
#include "vector.h"
#include <stdlib.h>

#include <stdio.h>

int			plane_intersect(void *data, t_dvec3 ray, t_dvec3 e, t_iparam *p)
{
	t_plane		*plane;
	t_dvec3		ep;
	t_dvec3		i_p;
	double		t;
	double		vn;

	plane = data;
	if((vn = dot_product(ray, plane->n)) == 0.0)
		return (0);
	get_vector(&ep, plane->plane_point, -1, e);
	t = dot_product(ep, plane->n) / vn;
	get_vector(&i_p, e, t, ray);
	if (t <= 0.01 || (p && p->t > 0 && p->t <= t))
		return (0);
	if (!p)
		return (1);
	get_vector(&p->i_point, e, t, ray);
	get_vector(&p->normal, plane->n, 0, plane->n);
	get_vector(&p->v, e, -1, p->i_point);
	norm_vector(&p->v);
	p->t = t;
	p->color = plane->color;
	return (1);
}

void		*read_plane(int fd)
{
	t_obj_3d	*shape;
	t_plane		*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	read_vector_fild(&plane->n, "\tn => ", fd);
	read_vector_fild(&plane->plane_point, "\tpoint => ", fd);
	plane->color = read_int_fild("\tcolor => ", 16, fd);
	norm_vector(&plane->n);
	shape = (t_obj_3d *)malloc(sizeof(t_obj_3d));
	shape->data = plane;
	shape->intersect = &plane_intersect;
	return (shape);
}
