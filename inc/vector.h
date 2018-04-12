
#ifndef VECTOR_H
# define VECTOR_H

# ifndef STRUCT_H
typedef double			t_dvec3[3];
# endif

void		norm_vector(t_dvec3 *vec);
void		vector_product(t_dvec3 *prod, t_dvec3 a, t_dvec3 b);
double		dot_product(t_dvec3 a, t_dvec3 b);
void		get_vector(t_dvec3 *res_v, t_dvec3 a, double sing, t_dvec3 b);

#endif