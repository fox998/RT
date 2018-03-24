/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 12:49:56 by afokin            #+#    #+#             */
/*   Updated: 2018/03/24 13:10:13 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	OBJ_H
# define OBJ_H

typedef double		t_dvec3[3];

typedef int			t_ivec3[3];

typedef	struct		s_obj_3d
{
	void		*data;
	int			(*check)(void *data);
}					t_obj_3d

#endif
