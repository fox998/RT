/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 17:50:37 by afokin            #+#    #+#             */
/*   Updated: 2018/05/02 17:50:43 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "my_sdl.h"
#include "vector.h"
#include "function.h"
#include <stdio.h>
#include "libft.h"

static void				get_rey(t_cam *cam, t_dvec3 *ray, double *c_cor)
{
	ray[0][0] = cam->dir[0] * 1.5 + cam->u[0] * c_cor[1] + cam->r[0] * c_cor[0];
	ray[0][1] = cam->dir[1] * 1.5 + cam->u[1] * c_cor[1] + cam->r[1] * c_cor[0];
	ray[0][2] = cam->dir[2] * 1.5 + cam->u[2] * c_cor[1] + cam->r[2] * c_cor[0];
}


static void				dop(t_obj_3d *shepe,
						t_shading *s, t_iparam p, t_light *lights)
{
	double		tmp;

	if (!shepe)
	{
		get_vector(&s->h, lights->dir, 1, p.v);
		norm_vector(&s->h);
		s->h_dot_n = dot_product(s->h, p.normal);
		tmp = fmax(0, dot_product(p.normal, lights->dir)) * s->l_intens;
		s->lambert += tmp;
		s->phong += ((tmp <= 0.0 ? 0 : pow(s->h_dot_n, 50.0))) * s->l_intens;
	}
}

static void				shading(t_light *lights,
						t_color *color, t_iparam p, t_obj_3d **shepe)
{
	t_shading	s;
	int			i;

	*color = *(t_color *)&p.color;
	s.a_intens = 0;
	s.lambert = 0;
	s.phong = 0;
	while (lights)
	{
		s.l_intens = lights->intensity;
		s.a_intens = fmax((0.15) * s.l_intens, s.a_intens);
		i = 0;
		while (shepe[i] &&
		!shepe[i]->intersect(shepe[i]->data, lights->dir, p.i_point, NULL))
			i++;
		dop(shepe[i], &s, p, lights);
		lights = lights->next;
	}
	color->r = fmin(0xFF, color->r * (s.a_intens + s.lambert) + s.phong * 0x8F);
	color->g = fmin(0xFF, color->g * (s.a_intens + s.lambert) + s.phong * 0x8F);
	color->b = fmin(0xFF, color->b * (s.a_intens + s.lambert) + s.phong * 0x8F);
}

static unsigned int		get_pixel_color(t_window *wind,
						double *cam_cor, t_obj_3d **shepe)
{
	t_dvec3		vray;
	t_iparam	p;
	t_color		color;
	int			i;
	int			num;


	get_rey(wind->cam, &vray, (double *)cam_cor);
	norm_vector(&vray);
	i = -1;
	p.t = -1;
	num = 0;
	p.txr = wind->txr;
	while (shepe[++i])
	{
		num += shepe[i][0].intersect(shepe[i][0].data, vray, wind->cam->pos, &p);
	}
	if (num)
		shading(wind->scn->lit, &color, p, shepe);
	else
		*((unsigned int *)&color) = skybox_mapping(vray, wind->skybox);
	return (*(unsigned int *)&color);
}


int		thread_f(void *data)
{
	t_thread	*t;
	double		cam_cor[2];
	int			x;
	t_window	*wind;

	t = data;
	x = -1;
	wind = t->wind;
	cam_cor[1] = (1.0 - 2.0 * t->i / (double)t->wind->h);
	while (++x < wind->w)
	{
		cam_cor[0] = (2.0 * x / (double)wind->w - 1.0);
		t->wind->pixs[t->i * wind->w + x] = get_pixel_color(wind, cam_cor, ((t_scene *)wind->scn)->obj);
	}
	return (0);
}

void					render(void *w)
{
	int			y;
	t_window	*wind;
	t_thread	t[((t_window *)w)->h];

	y = -1;
	wind = w;
	SDL_LockTexture(wind->tex_ptr, NULL, (void *)&wind->pixs, &wind->pitch);
	while (++y < wind->h)
	{
		t[y].wind = wind;
		t[y].i = y;
		t[y].thread = SDL_CreateThread(thread_f, "", (void *)&t[y]);
	}
	y = -1;
	while (++y < wind->h)
		SDL_WaitThread(t[y].thread, NULL);
	SDL_UnlockTexture(wind->tex_ptr);
	SDL_RenderCopy(wind->ren, wind->tex_ptr, NULL, NULL);
	SDL_RenderPresent(wind->ren);
}
