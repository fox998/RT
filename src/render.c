
#include "struct.h"
#include "my_sdl.h"
#include "vector.h"

static void		get_rey(t_cam *cam, t_dvec3 *ray, double *cam_cor)
{
	ray[0][0] = cam->dir[0] * 1.5 + cam->u[0] * cam_cor[1] + cam->r[0] * cam_cor[0];
	ray[0][1] = cam->dir[1] * 1.5 + cam->u[1] * cam_cor[1] + cam->r[1] * cam_cor[0];
	ray[0][2] = cam->dir[2] * 1.5 + cam->u[2] * cam_cor[1] + cam->r[2] * cam_cor[0];
}

#include <stdio.h>

static unsigned int		shading(t_light *lights, t_color *color, t_iparam p, t_obj_3d **shepe)
{
	double		ambient_intens;
	double		l_intens;
	t_shading	s;
	int			i;

	double tmp;

	*color = *(t_color *)&p.color;
	ambient_intens = 0;
	s.lambert = 0;
	s.phong = 0;
	while (lights)
	{
		l_intens = 0.8;
		ambient_intens += (0.08 / (i + 1)) * l_intens;
		i = 0;
		while (shepe[i] && !shepe[i]->intersect(shepe[i]->data, lights->dir, p.i_point, NULL))
			i++;
		if (!shepe[i])
		{
			get_vector(&s.h, lights->dir, 1, p.v);
			norm_vector(&s.h);
			s.h_dot_n = dot_product(s.h, p.normal);
			tmp = fmax(0,dot_product(p.normal, lights->dir)) * l_intens;
			s.lambert += tmp;
			s.phong += (( tmp <= 0.0 ? 0 : pow(s.h_dot_n, 50.0))) * l_intens;
		}
		lights = lights->next;
	}
	color->r = fmin(0xFF, color->r * (ambient_intens + s.lambert) + s.phong * 0x8F);
	color->g = fmin(0xFF, color->g * (ambient_intens + s.lambert) + s.phong * 0x8F);
	color->b = fmin(0xFF, color->b * (ambient_intens + s.lambert) + s.phong * 0x8F);
	return(*(unsigned int*)color);
}

static void		get_pixel_color(t_window *wind, double *cam_cor, t_obj_3d **shepe)
{
	t_dvec3		vray;
	t_iparam	p;
	t_color		color;
	int			i;

	get_rey(wind->cam, &vray, (double *)cam_cor);
	norm_vector(&vray);
	*((unsigned int *)&color) = 0;
	i = -1;
	p.t = -1;
	while (shepe[++i])
		if (shepe[i][0].intersect(shepe[i][0].data, vray, wind->cam->pos, &p))
			shading(wind->scn->lit, &color, p, shepe);
	SDL_SetRenderDrawColor(wind->ren, color.r, color.g, color.b, 0xFF);
}

void	render(void *w)
{
	int			x;
	int			y;
	double		cam_cor[2];
	t_window	*wind;

	y = -1;
	wind = w;
	while (++y < wind->h)
	{
		x = -1;
		cam_cor[1] = (1.0 - 2.0 * y / (double)wind->h);
		while (++x < wind->w)
		{
			cam_cor[0] = (2.0 * x / (double)wind->w - 1.0);
			get_pixel_color(wind, cam_cor, ((t_scene *)wind->scn)->obj);
			SDL_RenderDrawPoint(wind->ren, x, y);
		}
	}
}