
#include "struct.h"
#include "function.h"
#include "math.h"
#include "vector.h"
#include <stdlib.h>

#include <stdio.h>

int			sphere_intersect(void *data, t_dvec3 ray, t_dvec3 e, t_iparam *p)
{
	double		dsc;
	double		dxd;
	double		t;
	t_dvec3		ce;
	t_sphere	*s;

	s = data;
	dxd = dot_product(ray, ray);
	get_vector(&ce, e, -1, s->center);
	dsc = 4.0 * pow(dot_product(ray, ce), 2) - 4.0 * dxd * (dot_product(ce, ce) - s->r * s->r);
	if (dsc < 0 ||
	(t = (-2 * dot_product(ray, ce) - sqrt(fabs(dsc))) / (2.0 * dxd)) <= 0.001 ||
	(p && p->t <= t && p->t >= 0))
		return (0);
	if (!p)
		return(1);
	p->t = t;
	get_vector(&p->i_point, e, t, ray);
	get_vector(&p->normal, p->i_point, -1, s->center);
	get_vector(&p->v, e, -1, p->i_point);
	norm_vector(&p->v);
	norm_vector(&p->normal);
	p->color = s->color;
	return (1);
}

void		*read_sphere(int fd)
{
	t_sphere	*sphere;
	t_obj_3d	*shape;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	shape = (t_obj_3d *)malloc(sizeof(t_obj_3d));
	read_vector_fild(&sphere->center, "\tcenter => ", fd);
	sphere->r = fmax(1, read_int_fild("\tr => ", 10, fd));
	sphere->color = read_int_fild("\tcolor => ", 16, fd);
	printf("%i\n",sphere->color);
	shape->data = sphere;
	shape->intersect = &sphere_intersect;
	return (shape);
}