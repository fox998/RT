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

// static void			wind_init(t_window *wind)
// {

// }


int main(int argc, char **argv)
{
	t_window wind;

	if (argc != 2)
		usage('f');
	read_scene(argv[argc - 1], &wind);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		printf("!\n");
	wind.win = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	wind.srf = SDL_GetWindowSurface((SDL_Window *)wind.win);
	wind.img = SDL_LoadBMP("hello_world.bmp");
	if (!wind.img)
		printf("*\n");
	SDL_BlitSurface(wind.img, 0, wind.srf, 0);
	SDL_UpdateWindowSurface(wind.win);
	SDL_Delay( 5000 );
	return (0);
}
