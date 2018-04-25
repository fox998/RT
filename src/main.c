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
#include "struct.h"
#include "my_sdl.h"

#include <stdio.h>

static void			init(t_window *wind, char *path)
{
	int	i;

	i = SDL_Init(SDL_INIT_VIDEO);
	wind->w = 840;
	wind->h = 840;
	wind->win = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, wind->w, wind->h, SDL_WINDOW_SHOWN);
	wind->ren = SDL_CreateRenderer(wind->win, -1, SDL_RENDERER_ACCELERATED);
	if (i || !wind->win || !wind->ren)
		str_usage((char *)SDL_GetError());
	wind->scn = malloc(sizeof(t_scene));
	read_scene(path, wind);
	if (!wind->cam)
		usage('s');
	get_scene(wind);
}

int main(int argc, char **argv)
{
	t_window	wind;
	int			f;
	SDL_Event	e;

	if (argc != 2)
		usage('f');
	init(&wind, argv[argc - 1]);
	render(&wind);
	SDL_RenderPresent(wind.ren);
	f = 1;
	while (f)
	{
		while (SDL_PollEvent(&e) != 0 && f)
			if (e.type == SDL_QUIT ||
			(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
				f = 0;
	}
	return (0);
}
