/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 13:10:29 by afokin            #+#    #+#             */
/*   Updated: 2018/03/25 13:10:32 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

void		usage(char f);
void		read_cam(int fd);
void		read_win(int fd);
void		read_scene(char *path);

#endif
