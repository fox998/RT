
#include "vector.h"
#include "function.h"
#include <math.h>

void		norm_vector(t_dvec3 *vec)
{
	double		len;

	len = (sqrt(vec[0][0] * vec[0][0] + vec[0][1] * vec[0][1] +
	vec[0][2] * vec[0][2]));
	if (fabs(len) < 0.1)
		str_usage("Eror: Zero vector");
	vec[0][0] /= len;
	vec[0][1] /= len;
	vec[0][2] /= len;
}

void		vector_product(t_dvec3 *prod, t_dvec3 a, t_dvec3 b)
{
	double	x;
	double	y;
	double	z;

	x = a[1] * b[2] - a[2] * b[1];
	y = a[2] * b[0] - a[0] * b[2];
	z = a[0] * b[1] - a[1] * b[0];
	(*prod)[0] = x;
	(*prod)[1] = y;
	(*prod)[2] = z;
}

double		dot_product(t_dvec3 a, t_dvec3 b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

void		get_vector(t_dvec3 *res_v, t_dvec3 a, double sing, t_dvec3 b)
{
	t_dvec3	tmp;

	tmp[0] = a[0] + b[0] * sing;
	tmp[1] = a[1] + b[1] * sing;
	tmp[2] = a[2] + b[2] * sing;
	res_v[0][0] = tmp[0];
	res_v[0][1] = tmp[1];
	res_v[0][2] = tmp[2];
}