
#include        "struct.h"
#include        "vector.h"
#include        "function.h"
#include        <stdlib.h>
#include        <math.h>

int      equation_4th_pow_for_tore(t_tore *tr, double *Q, double *abc, double *t, double *ray)
{
    double  abcde[5];
    double  d;
    double  fore_R_2;
    double  rots[4];
    int     roots_num;

    d = dot_product(Q, Q) + tr->R * tr->R - tr->r * tr->r;
    fore_R_2 = 4 * tr->R * tr->R;
    abcde[4] = 1;
    abcde[3] = 4 * dot_product(Q, ray);
    abcde[2] = 2 * d + abcde[3] * abcde[3] / 4 - fore_R_2 * abc[0];
    abcde[1] = abcde[3] * d - fore_R_2 * abc[1];
    abcde[0] = d * d - fore_R_2 * abc[2];
    roots_num = SolveQuartic(abcde, rots);
    *t = 1e-6;
    for (int i = 0; i < roots_num; i++)
        if (rots[i] > 1e-6 && (*t == 1e-6 || rots[i] < *t))
            *t = rots[i];
    return (*t > 1e-6);
}

void        get_abc(double *abc, double *Q, double *dir, double *ray)
{
    double      u;
    double      v;

    u = dot_product(dir, Q);
    v = dot_product(dir, ray);
    abc[0] = 1  - v * v;
    abc[1] = 2 * (dot_product(Q, ray) - u * v);
    abc[2] = dot_product(Q, Q) - u * u;
}

void        get_normal(t_dvec3 *normal, double *point, t_tore *t)
{
    double      y;
    t_dvec3     D;
    t_dvec3     X;

    get_vector(&D, point , -1, t->pos);
    y = dot_product(D, t->dir);
    get_vector(&X, D, -y, t->dir);
    norm_vector(&X);
    X[0] *= t->R;    
    X[1] *= t->R;
    X[2] *= t->R; 
    get_vector(normal, D, -1, X);
    norm_vector(normal);  
}

int			tore_intersect(void *data, t_dvec3 ray, t_dvec3 e, t_iparam *p)
{
    t_tore      *t;
    double      te;
    double      abc[3];
    t_dvec3     Q;

    t = data;
    get_vector(&Q, e , -1, t->pos);
    get_abc(abc, Q, t->dir, ray);
    if (abc[1] * abc[1] - 4 * abc[0] * (abc[2]  - (t->R + t->r) * (t->R + t->r)) < 0 ||
        !equation_4th_pow_for_tore(t, Q, abc, &te, ray) || (p && p->t > 0 && p->t < te))       
        return 0;
    if (p)
    {
        get_vector(&p->i_point, e, te, ray);
        get_vector(&p->v, e, -1, p->i_point);
	    norm_vector(&p->v);
        get_normal(&p->normal, p->i_point, t);
        p->color = texture_mapping(p, t->pos, p->i_point, CYBE_CORD, 0);
    }
    return (1);
}

void		*read_tore(int fd)
{
    t_tore      *t;
    t_obj_3d    *shape;

    t = (t_tore *)malloc(sizeof(t_tore));
    shape = (t_obj_3d *)malloc(sizeof(t_obj_3d));
    read_vector_fild(&t->pos, "\tpos => ", fd);
    read_vector_fild(&t->dir, "\tdir => ", fd);
    norm_vector(&t->dir);
    t->color = read_int_fild("\tcolor => ", 16, fd);
    t->R = read_int_fild("\tR => ", 10, fd);
    t->r = read_int_fild("\tr => ", 10, fd);
    shape->data = t;
    shape->intersect = &tore_intersect;
    return (shape);
}