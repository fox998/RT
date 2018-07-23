
#include    "struct.h"
#include    "function.h"
#include    "vector.h"
#include    "math.h"

void                normal_disturbance(void *intersect_param)
{
    t_iparam        *p;

    p = intersect_param;

    /*
    //normal
    p->normal[0] = cos(p->i_point[0]) + p->normal[0];
    norm_vector(&p->normal);
    */


    /*
    //checkerboard
    p->color = 0xFFFFFF * (((int)round(p->i_point[0]) & 1) ^ ((int)round(p->i_point[0]) ? 1 : 0);
    */


    //Disturbance of the color
    t_color         *color;
    color = (t_color         *)&p->color;
    color->r = 0xFF * (0.5 + sin(p->i_point[0]) / (2 * M_PI));
    color->g = 0xFF * (0.5 + sin(p->i_point[1]) / (2 * M_PI));
    color->b = 0xFF * (0.5 + sin(p->i_point[2]) / (2 * M_PI));


    //
    //x = round(p->i_point[0]);
    //y = round(p->i_point[1]);
    //p->color = 0xFFFFFF * (((int)round(p->i_point[0]) & 1) ^ ((int)round(p->i_point[0]) ? 1 : 0);
    //p->color = p->color * cos(p->i_point[0]) + p->color;
    //p->color = cos(p->i_point[0]) * p->color;

}