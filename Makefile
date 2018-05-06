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
		obj_cone.c

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

OBJ_FLAG = -Wextra -Werror -Wall

SDL_FLAG :=

ifeq ($(shell uname), Linux)
	SDL_FLAG = -lSDL2
else
	SDL_FLAG = -framework SDL2 -F /Library/Frameworks/
endif

LIN_FLAG = $(SDL_FLAG) -lm

CC = gcc

NAME = RTv1

vpath %.c $(SRC_DIR)

.PHONY : all clean fclean re sdlfclean

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIN_FLAG) $(LIBFT) -o $(NAME)

$(LIBFT): 
	make -C $(LIBFT_DIR)

$(OBJ_DIR)%.o:%.c
	$(CC) $(OBJ_FLAG) -c $< -o $@ -I$(INC_DIR) -I$(LIBFT_DIR) -I/Library/Frameworks/SDL2.framework/Headers/

clean:
	rm -f $(OBJ)

libfclean:
	make fclean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)

relib:
	make re -C $(LIBFT_DIR)

re: fclean all

reall: libfclean re
