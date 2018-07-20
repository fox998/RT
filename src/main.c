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
#include <unistd.h>

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

void			*init_skybox()
{
	SDL_Surface		**arr;

	arr = malloc(sizeof(SDL_Surface *) * 6);
	arr[1] = IMG_Load("pinkback.jpg");
	arr[0] = IMG_Load("pinkfront.jpg");
	arr[2] = IMG_Load("pinkleft.jpg");
	arr[3] = IMG_Load("pinkright.jpg");
	arr[4] = IMG_Load("pinktop.jpg");
	arr[5] = IMG_Load("pinkbot.jpg");
	arr[0] = SDL_ConvertSurfaceFormat(arr[0], SDL_PIXELFORMAT_ARGB8888, 0);
	arr[1] = SDL_ConvertSurfaceFormat(arr[1], SDL_PIXELFORMAT_ARGB8888, 0);
	arr[2] = SDL_ConvertSurfaceFormat(arr[2], SDL_PIXELFORMAT_ARGB8888, 0);
	arr[3] = SDL_ConvertSurfaceFormat(arr[3], SDL_PIXELFORMAT_ARGB8888, 0);
	arr[4] = SDL_ConvertSurfaceFormat(arr[4], SDL_PIXELFORMAT_ARGB8888, 0);
	arr[5] = SDL_ConvertSurfaceFormat(arr[5], SDL_PIXELFORMAT_ARGB8888, 0);
	SDL_LockSurface(arr[0]);
	SDL_LockSurface(arr[1]);
	SDL_LockSurface(arr[2]);
	SDL_LockSurface(arr[3]);
	SDL_LockSurface(arr[4]);
	SDL_LockSurface(arr[5]);
	printf("%p\n", arr[0]);
	return (arr);
}

int				main(int argc, char **argv)
{
	t_window	wind;
	int			f;
	SDL_Event	e;

	if (argc != 2)
		usage('f');
	init(&wind, argv[argc - 1]);
	f = 1;
	SDL_Surface *txr;
	IMG_Init(IMG_INIT_JPG);
	txr =  SDL_LoadBMP("Stone_02_COLOR.bmp");
	txr = SDL_ConvertSurfaceFormat(txr, SDL_PIXELFORMAT_ARGB8888, 0);
	int a = SDL_LockSurface(txr);

	wind.nrml_txr = SDL_LoadBMP("Stone_02_NRM.bmp");
	wind.nrml_txr = SDL_ConvertSurfaceFormat(wind.nrml_txr, SDL_PIXELFORMAT_ARGB8888, 0);
	SDL_LockSurface(wind.nrml_txr);
	printf("nrm %p\n", wind.nrml_txr);
	wind.txr = txr;
	wind.skybox = init_skybox();
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
