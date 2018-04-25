#include "struct.h"
#include "function.h"
#include "vector.h"
#include <stdlib.h>
#include <math.h>

void		*read_light(int fd)
{
	t_light		*light;
	int			tmp;
	//t_obj_3d	*shepe;

	light = (t_light *)malloc(sizeof(t_light));
	//shepe = (t_obj_3d *)malloc(sizeof(t_obj_3d));
	read_vector_fild(&light->dir, "\tdir => ", fd);
	norm_vector(&light->dir);
	return (light);
}