/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 10:40:52 by afokin            #+#    #+#             */
/*   Updated: 2018/03/24 10:41:41 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "vector.h"
#include "struct.h"
#include "my_sdl.h"

static void		init(t_window *wind, char *path)
{
	int	i;

	i = SDL_Init(SDL_INIT_VIDEO);
	wind->w = 840;
	wind->h = 840;
	wind->win = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, wind->w, wind->h, SDL_WINDOW_SHOWN);
	wind->ren = SDL_CreateRenderer(wind->win, -1, SDL_RENDERER_ACCELERATED);
	wind->tex_ptr = SDL_CreateTexture(wind->ren, SDL_PIXELFORMAT_ARGB8888,
					SDL_TEXTUREACCESS_STREAMING,
					wind->w, wind->h);
	if (i || !wind->win || !wind->ren)
		str_usage((char *)SDL_GetError());
	wind->scn = malloc(sizeof(t_scene));
	wind->scn->obj = 0;
	read_scene(path, wind);
	if (!wind->cam)
		usage('s');
	get_scene(wind);
}

static int		c(t_cam *cam, t_dvec3 v, int sing)
{
	double		delt;

	delt = 0.8;
	get_vector(&cam->pos, cam->pos, (double)delt * sing, v);
	return (1);
}

static int	check_k(SDL_Event e, t_window *wind)
{
	if (e.type == SDL_KEYDOWN &&
	((e.key.keysym.sym == SDLK_w ? c(wind->cam, wind->cam->dir, 1) : 0) ||
	(e.key.keysym.sym == SDLK_s ? c(wind->cam, wind->cam->dir, -1) : 0) ||
	(e.key.keysym.sym == SDLK_a ? c(wind->cam, wind->cam->r, -1) : 0) ||
	(e.key.keysym.sym == SDLK_d ? c(wind->cam, wind->cam->r, 1) : 0) ||
	(e.key.keysym.sym == SDLK_SPACE ? c(wind->cam, wind->cam->u, 1) : 0) ||
	(e.key.keysym.sym == SDLK_LCTRL ? c(wind->cam, wind->cam->u, -1) : 0)))
		return (1);
	return (0);
}

#include <stdio.h>

int				main(int argc, char **argv)
{
	t_window	wind;
	int			f;
	SDL_Event	e;

	if (argc != 2)
		usage('f');
	init(&wind, argv[argc - 1]);
	f = 1;
	render(&wind);
	while (f)
		while (SDL_PollEvent(&e) != 0 && f)
		{
			e.type == SDL_QUIT || (e.type == SDL_KEYDOWN &&
			e.key.keysym.sym == SDLK_ESCAPE) ? (f = 0) : 0;
			if (check_k(e, &wind))
				render(&wind);
		}
	SDL_DestroyRenderer(wind.ren);
	SDL_Quit();
	return (0);
}
