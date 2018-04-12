#include "struct.h"
#include "function.h"
#include <stdlib.h>

void		*read_light(int fd)
{
	t_light		*light;
	//t_obj_3d	*shepe;

	light = (t_light *)malloc(sizeof(t_light));
	//shepe = (t_obj_3d *)malloc(sizeof(t_obj_3d));
	read_vector_fild(&light->pos, "\tpos => ", fd);
	return (light);
}