
#include        "struct.h"

double      quadratic_equation(double a, double b, double c)
{
    double      t;


    return      t;
}

void     mtx_mult_vtr_4d(double  mtx[4][4], double   *vec)
{

}

int			quric_intersect(void *data, t_dvec3 ray, t_dvec3 e, t_iparam *p)
{
    double		t;
    double      mtx[4][4];
    t_qudric    *q;

    q = data;
    mtx[0][0] = q->prm[0];
    mtx[0][1] = q->prm[1];
    mtx[0][2] = q->prm[2];
    mtx[0][3] = q->prm[3];

    mtx[1][0] = q->prm[1];
    mtx[1][1] = q->prm[4];
    mtx[1][2] = q->prm[5];
    mtx[1][3] = q->prm[6];

    mtx[2][0] = q->prm[2];
    mtx[2][1] = q->prm[5];
    mtx[2][2] = q->prm[7];
    mtx[2][3] = q->prm[8];

    mtx[3][0] = q->prm[3];
    mtx[3][1] = q->prm[6];
    mtx[3][2] = q->prm[8];
    mtx[3][3] = q->prm[9];
    

}

void		*read_qudric(int fd)
{
    t_qudric	*q;
	t_obj_3d	*shape;

	q = (t_sphere *)malloc(sizeof(t_qudric));
	shape = (t_obj_3d *)malloc(sizeof(t_obj_3d));
    q->prm[0] = 0;
    q->prm[1] = 0;
    q->prm[2] = 0;
    q->prm[3] = 0;
    q->prm[4] = 0;
    q->prm[5] = 0;
    q->prm[6] = 0;
    q->prm[7] = 0;
    q->prm[8] = 0;
    q->prm[9] = 0;
    shape->data = q;
    return (shape);
}