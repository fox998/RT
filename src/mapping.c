
#include "my_sdl.h"
#include "struct.h"
#include "function.h"
#include "vector.h"

void		sphere_cord(double *center, double *point, double *u, double *v)
{
	t_dvec3		d;

	get_vector(&d, point, -1, center);
	norm_vector(&d);

	*u = 0.5 + atan2(d[1], d[0]) / (M_PI * 2);
	*v = 0.5 + asin(d[2]) / M_PI;
}

void		cylinder_cord(double *center, double *point, double *u, double *v, int h, double *dir )
{
	t_dvec3		d;

	get_vector(&d, point, -1, center);
    d[2] = 0;
	norm_vector(&d);
	get_vector(&tmp[0], p->i_point, -1, c->pos);
	get_vector(&tmp[0], c->pos, dot_product(c->dir, tmp[0]), c->dir);
	get_vector(&p->normal, p->i_point, -1, tmp[0]);

	*u = 0.5 + atan2(d[1], d[0]) / (M_PI * 2);
	*v = fabs(point[2] - center[2])/5 - (int)fabs(point[2] - center[2]) / 5;//0.5 + sin((point[2] - center[2]) * 0.25) / 2;
}

unsigned int		texture_mapping(void *txr, double *center, double *point, int cord_flag, double *dir)
{
	double				u;
	double				v;
	int					x;
	int					y;
	unsigned int				*ptr;
    SDL_Surface                 *t;

    t = txr;
    if (cord_flag == SPHERE_CORD)
	    sphere_cord(center, point, &u, &v);
    else
        cylinder_cord(center, point, &u, &v, t->h, dir);
	x = u * t->w;
	y = v * t->h;
	ptr = t->pixels;
	return ptr[y * t->w + x];
}