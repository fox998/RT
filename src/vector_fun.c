/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 18:56:13 by afokin            #+#    #+#             */
/*   Updated: 2018/05/02 18:56:20 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "function.h"
#include <math.h>

void			norm_vector(t_dvec3 *vec)
{
	double		len;

	len = (sqrt(vec[0][0] * vec[0][0] + vec[0][1] * vec[0][1] +
	vec[0][2] * vec[0][2]));
	if (len == 0.0)
		return ;
	vec[0][0] /= len;
	vec[0][1] /= len;
	vec[0][2] /= len;
	vec[0][3] = 1;
}

void			vector_product(t_dvec3 *prod, t_dvec3 a, t_dvec3 b)
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

double			dot_product(t_dvec3 a, t_dvec3 b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

#include <stdio.h>

void			get_vector(t_dvec3 *res_v, t_dvec3 a, double sing, double *b)
{
	t_dvec3	tmp;

	tmp[0] = a[0] + b[0] * sing;
	tmp[1] = a[1] + b[1] * sing;
	tmp[2] = a[2] + b[2] * sing;
	res_v[0][0] = tmp[0];
	res_v[0][1] = tmp[1];
	res_v[0][2] = tmp[2];
}


void			multp_vect_to_matrix(double matrix[3][3], double *vec)
{
	t_dvec3		rec;

	rec[0] = matrix[0][0] * vec[0] + matrix[0][1] * vec[1] + matrix[0][2] * vec[2];
	rec[1] = matrix[1][0] * vec[0] + matrix[1][1] * vec[1] + matrix[1][2] * vec[2];
	rec[2] = matrix[2][0] * vec[0] + matrix[2][1] * vec[1] + matrix[2][2] * vec[2];
	vec[0] = rec[0];	
	vec[1] = rec[1];
	vec[2] = rec[2];	
}

void			to_new_basis(t_dvec3 u, t_dvec3 w, t_dvec3 r, t_dvec3 vec)
{
	double		matrix[3][3];
	double		det;

	matrix[0][0] = u[0];
	matrix[0][1] = w[0];
	matrix[0][2] = r[0];
	matrix[1][0] = u[1];
	matrix[1][1] = w[1];
	matrix[1][2] = r[1];
	matrix[2][0] = u[2];
	matrix[2][1] = w[2];
	matrix[2][2] = r[2];
	multp_vect_to_matrix(matrix, vec);
}
