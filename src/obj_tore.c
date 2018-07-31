
#include        "struct.h"
#include        "vector.h"
#include        "function.h"
#include        <stdlib.h>
#include        <math.h>

int			tore_intersect(void *data, t_dvec3 ray, t_dvec3 e, t_iparam *p)
{
    t_obj_3d    *s;
    t_tore      *t;

    s = data;
    t = s->data;
    
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