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
	wind->w = 640;
	wind->h = 480;
	wind->win = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, wind->w, wind->h, SDL_WINDOW_SHOWN);
	wind->ren = SDL_CreateRenderer(wind->win, -1, SDL_RENDERER_ACCELERATED);
	if (i || !wind->win || !wind->ren)
		str_usage((char *)SDL_GetError());
	wind->scn = malloc(sizeof(t_scene));
	read_scene(path, wind);
	get_scene(wind);
}

int main(int argc, char **argv)
{
	t_window wind;

	if (argc != 2)
		usage('f');
	init(&wind, argv[argc - 1]);
	//SDL_SetRenderDrawColor(wind.ren, 0,0, 0xFF, 0xFF);
	render(&wind);
	SDL_RenderPresent(wind.ren);
	SDL_Delay( 5000 );
	return (0);
}
