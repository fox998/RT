
#include "struct.h"
#include "my_sdl.h"
#include "vector.h"

static void		get_rey(t_cam *cam, t_dvec3 *ray, double *cam_cor)
{
	ray[0][0] = cam->dir[0] + cam->u[0] * cam_cor[1] + cam->r[0] * cam_cor[0];
	ray[0][1] = cam->dir[1] + cam->u[1] * cam_cor[1] + cam->r[1] * cam_cor[0];
	ray[0][2] = cam->dir[2] + cam->u[2] * cam_cor[1] + cam->r[2] * cam_cor[0];
}

#include <stdio.h>

static unsigned int		shading(t_light *lights, t_color *color, t_iparam p)
{
	double		ambient_intens;
	double		l_intens;
	t_shading	s;

	l_intens = 0.6;
	ambient_intens = 0.1 * l_intens;
	*color = *(t_color *)&p.color;
	get_vector(&s.l,lights->pos, -1, p.i_point);
	norm_vector(&s.l);
	get_vector(&s.h, s.l, 1, p.v);
	norm_vector(&s.h);
	s.h_dot_n = dot_product(p.normal, s.h);
	s.phong = ((s.h_dot_n <= 0 ? 0 : pow(s.h_dot_n, 20))) * l_intens * 0xFF;
	s.lambert = fmax(0,dot_product(p.normal, s.l)) * l_intens;
	color->r = fmin(0xFF, color->r * (ambient_intens + s.lambert) + s.phong);
	color->g = fmin(0xFF, color->g * (ambient_intens + s.lambert) + s.phong);
	color->b = fmin(0xFF, color->b * (ambient_intens + s.lambert) + s.phong);
	return(*(unsigned int*)color);
}

static void		get_pixel_color(t_window *wind, double *cam_cor, t_obj_3d **shepe)
{
	t_dvec3		vray;
	t_iparam	p;
	t_color		color;

	get_rey(wind->cam, &vray, (double *)cam_cor);
	p.e[0] = wind->cam->pos[0];
	p.e[1] = wind->cam->pos[1];
	p.e[2] = wind->cam->pos[2];
	*((unsigned int *)&color) = 0;
	if (shepe[0][0].intersect(shepe[0][0].data, &vray, &p))
		shading(wind->scn->lit, &color, p);
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
		cam_cor[1] = (2.0 * y / wind->h - 1) * wind->h / wind->w;
		while (++x < wind->w)
		{
			cam_cor[0] = 2.0 * x / wind->w - 1;
			get_pixel_color(wind, cam_cor, ((t_scene *)wind->scn)->obj);
			SDL_RenderDrawPoint(wind->ren, x, y);
		}
	}
}