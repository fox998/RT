
#include        "struct.h"
#include        "vector.h"
#include        "function.h"
#include        <stdlib.h>
#include        <math.h>

int      quadratic_equation(double a, double b, double c, double *t)
{
    double      dscr;

    if ((dscr = b * b - 4 * a * c) < 0)
        return 0;
    else if (dscr == 0)
        *t = -b / (a + a);
    else
    {
        dscr = sqrt(dscr);
        *t = (-b - dscr) / (a + a);
        *t < 1e-6 ? (*t = (-b + dscr) / (a + a)) : 0;
    }
    return (*t > 1e-6);
}

void    mtx_mult_vtr_4d(double  matrix[4][4], double   *vec, double *res)
{
    double      v[4];

    v[0] = matrix[0][0] * vec[0] + matrix[0][1] * vec[1] + matrix[0][2] * vec[2] + matrix[0][3] * vec[3];
	v[1] = matrix[1][0] * vec[0] + matrix[1][1] * vec[1] + matrix[1][2] * vec[2] + matrix[1][3] * vec[3];
	v[2] = matrix[2][0] * vec[0] + matrix[2][1] * vec[1] + matrix[2][2] * vec[2] + matrix[2][3] * vec[3];
    v[3] = matrix[3][0] * vec[0] + matrix[3][1] * vec[1] + matrix[3][2] * vec[2] + matrix[3][3] * vec[3];
    
    res[0] = v[0];
    res[1] = v[1];
    res[2] = v[2];
    res[3] = v[3];
}


double      dot_prod_4d(double  *v1, double *v2)
{
    return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3]);
}

#include     <stdio.h>

int			qudric_intersect(void *data, t_dvec3 ray, t_dvec3 e, t_iparam *p)
{
    double		t;
    double      mtx[4][4];
    double    q[10];
    t_obj_3d	*obj;

    obj = data;
    //q = obj->data;
    q[0] = 5;
    q[1] = 0;
    q[2] = 0;
    q[3] = 0;

    q[4] = 5;
    q[5] = 0;
    q[6] = 0;

    q[7] = 0;
    q[8] = 1;
    q[9] = 0;
    //printf("intr %p\n", q);
    mtx[0][0] = q[0];
    mtx[0][1] = q[1];
    mtx[0][2] = q[2];
    mtx[0][3] = q[3];

    mtx[1][0] = q[1];
    mtx[1][1] = q[4];
    mtx[1][2] = q[5];
    mtx[1][3] = q[6];

    mtx[2][0] = q[2];
    mtx[2][1] = q[5];
    mtx[2][2] = q[7];
    mtx[2][3] = q[8];

    mtx[3][0] = q[3];
    mtx[3][1] = q[6];
    mtx[3][2] = q[8];
    mtx[3][3] = q[9];
    

    
    double      tmp[4];
    double      tmp2[4];
    tmp[3] = 1;
    tmp2[3] = 1;
    ray[3] = 1;
    e[3] = 1;
    mtx_mult_vtr_4d(mtx, ray, tmp);
    mtx_mult_vtr_4d(mtx, e, tmp2);
    if (!quadratic_equation(dot_prod_4d(tmp, ray), 2 * dot_prod_4d(tmp, e), dot_prod_4d(tmp2, e), &t) ||
        (p && p->t >= 0 && p->t <= t))
        return (0);
    if (p)
    {   
        p->t = t;
        get_vector(&p->i_point, e, t, ray);
        get_vector(&p->v, e, -1, p->i_point);
	    norm_vector(&p->v);
        p->normal[0] = (mtx[0][0] * p->i_point[0] + mtx[0][1] * p->i_point[1] + mtx[0][2] * p->i_point[2] + mtx[0][3]);
        p->normal[1] = (mtx[1][0] * p->i_point[0] + mtx[1][1] * p->i_point[1] + mtx[1][2] * p->i_point[2] + mtx[1][3]);
        p->normal[2] = (mtx[2][0] * p->i_point[0] + mtx[2][1] * p->i_point[1] + mtx[2][2] * p->i_point[2] + mtx[2][3]);
        norm_vector(&p->normal);
        p->color = 0xFF;
    }
    return (1);
}

void		*read_qudric(int fd)
{
    double	*q;
	t_obj_3d	*shape;

	//q = (t_qudric *)malloc(sizeof(t_qudric));
    q = (double *)malloc(sizeof(double) * 10);
	shape = (t_obj_3d *)malloc(sizeof(t_obj_3d));
    q[0] = 2;
    q[1] = 2;
    q[2] = -1;
    q[3] = 0;
    q[4] = 0;
    q[5] = 0;
    q[6] = 0;
    q[7] = 0;
    q[8] = 0;
    q[9] = 0;
    shape->data = q;
    printf("read %p\n", q);
    shape->intersect = &qudric_intersect;
    return (shape);
}