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

SDL_TAR := $(LIB_DIR)SDL2-2.0.7.tar.gz
SDL_DIR := $(SDL_TAR:.tar.gz=/)
SDL_INC := $(SDL_DIR)include/
SDL := $(SDL_DIR)build/.libs/libSDL2.a

LIBFT_DIR = $(LIB_DIR)libft/
LIBFT = $(LIBFT_DIR)libft.a

SRC := main.c read_obj.c read_scene.c usage.c num_line.c ft_atoi_base.c

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

OBJ_FLAG = -Wextra -Werror -Wall

LIN_FLAG = -framework SDL2 -F /Library/Frameworks/

CC = gcc

NAME = RTv1

vpath %.c $(SRC_DIR)

.PHONY : all clean fclean re sdlfclean

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(LIN_FLAG) $(LIBFT) $(OBJ) -o $(NAME)

$(LIBFT): 
	make -C $(LIBFT_DIR)

$(OBJ_DIR)%.o:%.c
	$(CC) $(OBJ_FLAG) -c $< -o $@ -I$(INC_DIR) -I$(LIBFT_DIR) -I/Library/Frameworks/SDL2.framework/Headers/

clean:
	echo $(OBJ)

sdlfclean:
	rm -rf $(SDL_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
