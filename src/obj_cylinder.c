
#include "struct.h"
#include "function.h"
#include "vector.h"
#include <stdlib.h>
#include <math.h>

int		cylinder_intersect(void *data, t_dvec3 ray, t_dvec3 eye, t_iparam *p)
{
	t_dvec3		tmp[2];
	t_dvec3		dp;
	double		t;
	double		d;
	double		abc[3];
	t_cylinder	*c;

	c = data;
	get_vector(&tmp[0], ray, -1 * dot_product(c->dir, ray), c->dir);
	abc[0] = dot_product(tmp[0], tmp[0]);
	get_vector(&dp, eye, -1, c->pos);
	get_vector(&tmp[1], dp, -1 * dot_product(dp, c->dir), c->dir);
	abc[1] = 2.0 * dot_product(tmp[0], tmp[1]);
	abc[2] = dot_product(tmp[1], tmp[1]) - c->r * c->r;
	d = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if ((d) < 0 ||
		(t = (-abc[1] - sqrt(d)) / (2.0 * abc[0])) <= 0.01 ||
		(p && p->t > 0 && p->t <= t))
		return (0);
	if (p)
	{
		p->t = t;
		get_vector(&p->i_point, eye, p->t, ray);
		get_vector(&p->v, eye, -1, p->i_point);
		get_vector(&tmp[0], p->i_point, -1, c->pos);
		get_vector(&tmp[0], c->pos, dot_product(c->dir, tmp[0]), c->dir);
		get_vector(&p->normal, p->i_point, -1, tmp[0]);
		norm_vector(&p->v);
		norm_vector(&p->normal);
		p->color = c->color;
	}
	return (1);
}

void	*read_cylinder(int fd)
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
	return(shape);
}