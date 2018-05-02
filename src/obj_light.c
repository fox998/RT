#include "struct.h"
#include "function.h"
#include "vector.h"
#include <stdlib.h>
#include <math.h>

void		*read_light(int fd)
{
	t_light		*light;
	int			tmp;

	light = (t_light *)malloc(sizeof(t_light));
	read_vector_fild(&light->dir, "\tdir => ", fd);
	light->intensity = fmax(1, read_int_fild("\tintensity => ", 10, fd)) / 100.0;
	norm_vector(&light->dir);
	return (light);
}