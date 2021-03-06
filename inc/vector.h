/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 18:02:39 by afokin            #+#    #+#             */
/*   Updated: 2018/05/03 18:02:42 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# ifndef STRUCT_H
typedef double			t_dvec3[4];
# endif

void		norm_vector(t_dvec3 *vec);
void		vector_product(t_dvec3 *prod, t_dvec3 a, double *b);
double		dot_product(t_dvec3 a, t_dvec3 b);
void		get_vector(t_dvec3 *res_v, t_dvec3 a, double sing, t_dvec3 b);
void		to_new_basis(t_dvec3 u, t_dvec3 w, t_dvec3 r, t_dvec3 vec);

#endif
