
#include        "struct.h"
#include        "vector.h"
#include        "function.h"
#include        <stdlib.h>
#include        <math.h>

int      equation_4th_pow_for_tore(t_tore *tr, double *Q, double *abc, double *t)
{
    double  abcde[5];
    double  d;
    double  fore_R_2;
    double  pqruyw[6];

    d = dot_product(Q, Q) + tr->R * tr->R - tr->r * tr->r;
    fore_R_2 = 4 * tr->R * tr->R;
    abcde[0] = 1;
    abcde[1] = 4 * dot_product(Q, tr->dir);
    abcde[2] = 2 * d + abcde[1] * abcde[1] / 4 - fore_R_2 * abc[0];
    abcde[3] = abcde[1] * d - fore_R_2 * abc[1];
    abcde[4] = d * d - fore_R_2 * abc[2];
    
    abc[0] = - 3 * abcde[1] * abcde[1] / 8 + abcde[2];
    abc[1] = abcde[1] * abcde[1] * abcde[1] / 8 - abcde[1] * abcde[2] / 2 + abcde[3];
    abc[2] = 3 * pow(abcde[1], 4) / 256 + pow(abcde[1], 2) * abcde[2] / 16 - abcde[1] * abcde[3] / 4 + abcde[4];

    pqruyw[0] = - abc[0] * abc[0] / 12 - abc[2];
    pqruyw[1] = - pow(abc[0], 3) / 108 + abc[0] * abc[2] / 3 - abc[1] * abc[1] / 8;
    pqruyw[2] = pqruyw[1] * pqruyw[1] / 4 + pow(pqruyw[0], 3) / 27;
    if (pqruyw[2] < 0)
        return 0;
    pqruyw[2] = -pqruyw[1] / 2 + sqrt(pqruyw[2]);
    pqruyw[3] = cbrt(pqruyw[2]);
    pqruyw[4] = - 5.0 * abc[0] / 6 + pqruyw[3] + (pqruyw[3] == 0 ? -cbrt(pqruyw[1]) : -pqruyw[0] / (3 * pqruyw[3]));
    pqruyw[5] = abc[0] + 2 * pqruyw[4];
    if (pqruyw[5] < 0)
        return 0;
    pqruyw[5] = sqrt(pqruyw[5]);
    
    double tmp;
    *t = 1e-6;
    if ((tmp = 3 * abc[0] + 2 * abc[2] - 2 * abc[1] / pqruyw[5]) > 0)
    {   
       *t = fmin(*t, fmax(1e-6, -abcde[1] / (4 * abcde[0]) + (-pqruyw[5] - sqrt(tmp)) / 2));
       *t = fmin(*t, fmax(1e-6, -abcde[1] / (4 * abcde[0]) + (-pqruyw[5] + sqrt(tmp)) / 2));
    }
    if ((tmp = 3 * abc[0] + 2 * abc[2] + 2 * abc[1] / pqruyw[5]) > 0)
    {   
       *t = fmin(*t, fmax(1e-6, -abcde[1] / (4 * abcde[0]) + (-pqruyw[5] - sqrt(tmp)) / 2));
       *t = fmin(*t, fmax(1e-6, -abcde[1] / (4 * abcde[0]) + (-pqruyw[5] + sqrt(tmp)) / 2));
    }
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
    t_obj_3d    *s;
    t_tore      *t;
    double      te;

    double      abc[3];
    t_dvec3     Q;

    s = data;
    t = s->data;

    get_vector(&Q, e , -1, t->pos);
    get_abc(abc, Q, t->dir, ray);
    if (abc[1] * abc[1] - 4 * abc[0] * (abc[2]  - (t->R + t->r) * (t->R + t->r)) < 0 ||
        !equation_4th_pow_for_tore(t, Q, abc, &te) || (p && p->t > 0 && p->t < te))
        return 0;
    if (p)
    {
        get_vector(&p->i_point, e, te, ray);
        get_vector(&p->v, e, -1, p->i_point);
	    norm_vector(&p->v);
        get_normal(&p->normal, p->i_point, t);
        p->color = t->color;
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
    t->color = read_int_fild("\tcolor => ", 16, fd);
    t->R = read_int_fild("\tR => ", 10, fd);
    t->r = read_int_fild("\tr => ", 10, fd);
    shape->data = t;
    shape->intersect = &tore_intersect;
    return (shape);
}