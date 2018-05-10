/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_sdl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 18:05:30 by afokin            #+#    #+#             */
/*   Updated: 2018/05/03 18:05:32 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_SDL_H
# define MY_SDL_H
# ifdef __APPLE__
#  include <SDL.h>
#  include <SDL_thread.h>
# else
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_thread.h>
# endif
#endif
