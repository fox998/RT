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

SRC := main.c

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

OBJ_FLAG = -Wextra -Werror -Wall

LIN_FLAG = 

CC = gcc

NAME = 

vpath %.c $(SRC_DIR)

.PHONY : all clean fclean re sdlfclean

all: $(NAME)

$(NAME): $(SDL) $(OBJ)
	%(СС) $(LIN_FLAG) -o $(NAME)

$(SDL): $(SDL_DIR)
	cd $(SDL_DIR) && make > /dev/null

$(SDL_DIR): $(SDL_TAR)
	tar -xf $(SDL_TAR) -C $(LIB_DIR)
	cd $(SDL_DIR) && ./configure > /dev/null

$(OBJ_DIR)%.o:%.c
	$(CC) $(OBJ_FLAG) -c $< -o $@ -I$(INC_DIR)

clean:
	echo $(OBJ)

sdlfclean:
	rm -rf $(SDL_DIR)

fclean: clean
	rm -f $(NAME)
	if test -f $(SDL_DIR)Makefile; then (make clean -C $(SDL_DIR)); fi
re: fclean all
