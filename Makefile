# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afokin <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/24 13:10:52 by afokin            #+#    #+#              #
#    Updated: 2018/03/25 12:19:04 by afokin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR := ./src/
LIB_DIR := ./lib/
INC_DIR := ./inc/
OBJ_DIR := ./obj/

LIBFT_DIR = $(LIB_DIR)libft/
LIBFT = $(LIBFT_DIR)libft.a

SRC :=	main.c\
		read_obj.c\
		read_scene.c\
		usage.c	num_line.c\
		ft_atoi_base.c\
		get_scene.c\
		vector_fun.c\
		render.c\
		obj_sphere.c\
		obj_light.c\
		obj_plane.c\
		obj_cylinder.c\
		obj_cone.c\
		obj_qudric.c\
		mapping.c\
		disturbance.c

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

OBJ_FLAG = -g
#-Wextra -Werror -Wall

INCLUDES	:=
FRAMEWORKS	:=

SDL_FLAG :=

ifeq ($(shell uname), Linux)
	SDL_FLAG = -lSDL2 -lSDL2_image
else
	SDL_FLAG = -framework SDL2 -F /Library/Frameworks/
	FRAMEWORKS	=	-F./frameworks \
				-rpath ./frameworks \
				-framework OpenGL -framework AppKit -framework OpenCl \
				-framework SDL2_ttf -framework SDL2_image \
				-framework SDL2_mixer -framework SDL2_net
	INCLUDES	=	-I./frameworks/SDL2.framework/Versions/A/Headers \
				-I./frameworks/SDL2_ttf.framework/Versions/A/Headers \
				-I./frameworks/SDL2_image.framework/Versions/A/Headers \
				-I./frameworks/SDL2_mixer.framework/Headers \
				-I./frameworks/SDL2_net.framework/Headers \
				-F./frameworks
endif

LIN_FLAG = $(SDL_FLAG) -lm -lpthread

CC = gcc

NAME = RTv1

vpath %.c $(SRC_DIR)

.PHONY : all clean fclean re sdlfclean

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIN_FLAG) $(LIBFT) -o $(NAME) $(FRAMEWORKS)

$(LIBFT): 
	make -C $(LIBFT_DIR)

$(OBJ_DIR)%.o:%.c
	$(CC) $(OBJ_FLAG) -c $< -o $@ -I$(INC_DIR) -I$(LIBFT_DIR) $(INCLUDES)

clean:
	rm -f $(OBJ)

libfclean:
	make fclean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)

fcleanall: fclean libfclean

relib:
	make re -C $(LIBFT_DIR)

re: fclean all

reall: relib re
