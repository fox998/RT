
#include "my_sdl.h"
#include "struct.h"
#include "function.h"
#include "vector.h"

void		sphere_cord(double *center, double *point, double *u, double *v)
{
	t_dvec3		d;

	get_vector(&d, point, -1, center);
	norm_vector(&d);

	*u = 0.5 + atan2(d[1], d[0]) / (M_PI * 2);
	*v = 0.5 + asin(d[2]) / M_PI;
}

void		plane_cord(double *center, double *point, double *u, double *v, double *n)
{
	t_dvec3		r;
	t_dvec3		w;
	t_dvec3		vec;

	r[0] = n[0];
	r[1] = n[1] - 0.001;
	r[2] = n[2] - 0.002;
	norm_vector(&r);
	vector_product(&w, n, r);
	norm_vector(&w);
	vector_product(&r, w, n);
	norm_vector(&r);
	get_vector(&vec, point, -1, center);
	to_new_basis(w, r, n, vec);
	//printf("plane cord %f %f %f\n", vec[0], vec[1], vec[2]);
	*u = (vec[0])/10 - (int)(vec[0])/ 10;
	*v = (vec[1])/10 - (int)(vec[1])/ 10;
}

void		box_cord(double *center, double *point, double *u, double *v)
{
	t_dvec3		dir;

	get_vector(&dir, point, -1, center);
	float absX = fabs(dir[0]);
	float absY = fabs(dir[1]);
	float absZ = fabs(dir[2]);
	
	int isXPositive = dir[0] > 0 ? 1 : 0;
	int isYPositive = dir[1] > 0 ? 1 : 0;
	int isZPositive = dir[2] > 0 ? 1 : 0;

	float maxAxis;
	
	// POSITIVE X
	if (isXPositive && absX >= absY && absX >= absZ) {
	// u (0 to 1) goes from +z to -z
	// v (0 to 1) goes from -y to +y
	maxAxis = absX;
	*u = -dir[2];
	*v = dir[1];
	}
	// NEGATIVE X
	else if (!isXPositive && absX >= absY && absX >= absZ) {
	// u (0 to 1) goes from -z to +z
	// v (0 to 1) goes from -y to +y
	maxAxis = absX;
	*u = dir[2];
	*v = dir[1];
	}
	// POSITIVE Y
	else if (isYPositive && absY >= absX && absY >= absZ) {
	// u (0 to 1) goes from -x to +x
	// v (0 to 1) goes from +z to -z
	maxAxis = absY;
	*u = dir[0];
	*v = -dir[2];
	}
	// NEGATIVE Y
	else if (!isYPositive && absY >= absX && absY >= absZ) {
	// u (0 to 1) goes from -x to +x
	// v (0 to 1) goes from -z to +z
	maxAxis = absY;
	*u = dir[0];
	*v = dir[2];
	}
	// POSITIVE Z
	else if (isZPositive && absZ >= absX && absZ >= absY) {
	// u (0 to 1) goes from -x to +x
	// v (0 to 1) goes from -y to +y
	maxAxis = absZ;
	*v = dir[1];
	*u = dir[0];
	}
	// NEGATIVE Z
	else if (!isZPositive && absZ >= absX && absZ >= absY) {
	// u (0 to 1) goes from +x to -x
	// v (0 to 1) goes from -y to +y
	maxAxis = absZ;
	*u = -dir[0];
	*v = dir[1];
	}
	//*u = 0.5f * (*u / maxAxis + 1.0f);
	//*v = 0.5f * (*v / maxAxis + 1.0f);
	*u /= maxAxis;
	*v /= maxAxis;
}

void		cylinder_cord(double *center, double *point, double *u, double *v, int h, double *dir )
{
	t_dvec3		d;
	t_dvec3		d2;
	t_dvec3		r = {0 , 1, 0};
	double		h2;

	//get_vector(&d, point, -1, center);
	get_vector(&d2, point, -1, center);
	h2 = dot_product(dir, d2);
	get_vector(&d2, center, dot_product(dir, d2), dir);
	get_vector(&d, point, -1, d2);
	norm_vector(&d);
	vector_product(&d2, dir, r);
	norm_vector(&d2);

	//*u = 0.5 + atan2(d[1], d[0]) / (M_PI * 2);
	*u = 0.5 + acos(dot_product(d, d2)) / (M_PI * 2);
	*v = h2/10 - (int)h2/ 10;//0.5 + sin((point[2] - center[2]) * 0.25) / 2;
}

unsigned int		texture_mapping(void *intersect_param, double *center, double *point, int cord_flag, double *dir)
{
	double				u;
	double				v;
	int					x;
	int					y;
	unsigned int				*ptr;
	SDL_Surface                 *t;
	t_iparam					*p;

	p = intersect_param;
	t = p->txr;
	if (cord_flag == SPHERE_CORD)
		sphere_cord(center, point, &u, &v);
	else if (cord_flag == CYLINDER_CORD)
		cylinder_cord(center, point, &u, &v, t->h, dir);
	else if (cord_flag == PLANE_CORD)
		plane_cord(center, point, &u, &v, dir);
	else
		box_cord(center, point, &u, &v);
	x = fmin((u >= 0 ? u : 1.0 + u) * t->w, t->w - 1);
	y = fmin((v >= 0 ? v : 1.0 + v) * t->h, t->h - 1);
	ptr = t->pixels;
	p->txr_cord = y * t->w + x;
	return  ptr[p->txr_cord];
}




unsigned int		skybox_mapping(double *dir, void *skybox)
{
	float absX = fabs(dir[0]);
	float absY = fabs(dir[1]);
	float absZ = fabs(dir[2]);

	SDL_Surface **arr = skybox;
	
	int isXPositive = dir[0] > 0 ? 1 : 0;
	int isYPositive = dir[1] > 0 ? 1 : 0;
	int isZPositive = dir[2] > 0 ? 1 : 0;
	
	int index;

	float maxAxis, uc, vc;
	
	// POSITIVE X
	if (isXPositive && absX >= absY && absX >= absZ) {
	// u (0 to 1) goes from +z to -z
	// v (0 to 1) goes from -y to +y
	maxAxis = absX;
	uc = -dir[1];
	vc = -dir[2];
	index = 0;
		//return 0x88;
	}
	// NEGATIVE X
	else if (!isXPositive && absX >= absY && absX >= absZ) {
	// u (0 to 1) goes from -z to +z
	// v (0 to 1) goes from -y to +y
	maxAxis = absX;
	uc = dir[1];
	vc = -dir[2];
	index = 1;
		//return 0xFF;
	}
	// POSITIVE Y
	else if (isYPositive && absY >= absX && absY >= absZ) {
	// u (0 to 1) goes from -x to +x
	// v (0 to 1) goes from +z to -z
	maxAxis = absY;
	uc = dir[0];
	vc = -dir[2];
	index = 2;
		//return 0x8800;
	}
	// NEGATIVE Y
	else if (!isYPositive && absY >= absX && absY >= absZ) {
	// u (0 to 1) goes from -x to +x
	// v (0 to 1) goes from -z to +z
	maxAxis = absY;
	uc = -dir[0];
	vc = -dir[2];
	index = 3;
		//return 0xFF00;
	}
	// POSITIVE Z
	else if (isZPositive && absZ >= absX && absZ >= absY) {
	// u (0 to 1) goes from -x to +x
	// v (0 to 1) goes from -y to +y
	maxAxis = absZ;
	uc = -dir[1];
	vc = dir[0];
	index = 4;
		//return 0x880000;
	}
	// NEGATIVE Z
	else if (!isZPositive && absZ >= absX && absZ >= absY) {
	// u (0 to 1) goes from +x to -x
	// v (0 to 1) goes from -y to +y
	maxAxis = absZ;
	uc = -dir[1];
	vc = -dir[0];
	index = 5;
		//return 0xFF0000;
	}
	uc = 0.5f * (uc / maxAxis + 1.0f);
	vc = 0.5f * (vc / maxAxis + 1.0f);

	int w = arr[index]->w * uc;
	int h = arr[index]->h * vc;
	unsigned int *pix = arr[index]->pixels;

	return (pix[w + h * arr[index]->w]);
}

void      normal_mapping(void *intersect_param)
{
	SDL_Surface	*txr;
	t_dvec3		r;
	t_dvec3		w;
	t_dvec3		new_n;
	t_color		rgb_n;
	t_iparam	*p;

	p = intersect_param;
	norm_vector(&p->normal);
	r[0] = p->normal[0];
	r[1] = p->normal[1] - 0.001;
	r[2] = p->normal[2] - 0.001;
	norm_vector(&r);
	//printf("my %f %f %f \ntxr %f %f %f\n",r[0], r[1], r[2], p->normal[0], p->normal[1], p->normal[2]);
	vector_product(&w, r, p->normal);
	norm_vector(&w);
	vector_product(&r, p->normal, w);
	norm_vector(&r);
	//printf("my %f %f %f \n", r[0], r[1], r[2]);
	txr = p->nrml_txr;
	rgb_n =	((t_color *)txr->pixels)[p->txr_cord];
	new_n[0] = rgb_n.r - 126;
	new_n[1] = rgb_n.g - 126;
	new_n[2] = rgb_n.b;
	norm_vector(&new_n);
	to_new_basis(r, w, p->normal, new_n);
	//printf("my %f %f %f \ntxr %f %f %f\n",r[0], r[1], r[2], new_n[0], new_n[1], new_n[2]);
	p->normal[0] = new_n[0];
	p->normal[1] = new_n[1];
	p->normal[2] = new_n[2];
}
