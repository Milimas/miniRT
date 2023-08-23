# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/04 11:54:50 by rouarrak          #+#    #+#              #
#    Updated: 2023/08/23 20:11:52 by aminebeihaq      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

CFLAGS += -Wall -Werror -Wextra #-fsanitize=address -g3

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CFLAGS += -D LINUX
	LDFLAGS += -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
	INCLUDES += -I/usr/include -Imlx_linux
endif
ifeq ($(UNAME_S),Darwin)
UNAME_P := $(shell uname -p)
ifeq ($(UNAME_P),arm)
	CC = arch -x86_64 gcc
endif
	CFLAGS += -I.
	INCLUDES += -Lmlx -lmlx -framework OpenGL -framework AppKit
endif

NAME = miniRT

BONUS = miniRT_bonus

LIBFT = libft.a
LIBFT_DIR = libft/

SRC =	main.c				\
		srcs/color.c		\
		srcs/put_pixel.c	\
		srcs/image.c		\

OBJ = $(SRC:.c=.o)

%.o: %.c
	echo $(UNAME_P)
	$(CC) $(CFLAGS)  -c $< -o $@ 

all: $(NAME) # $(BONUS)

$(NAME): $(OBJ) $(LIBFT) ./includes/minirt.h
	$(CC) $(OBJ) $(LIBFT) $(INCLUDES) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)
	mv $(LIBFT_DIR)$(LIBFT) .

bonus: $(BONUS)

$(BONUS): $(OBJ) $(LIBFT) ./includes/miniRT.h
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(INCLUDES) $(LDFLAGS) -o $(BONUS)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS)
	rm -f $(LIBFT)

re: clean fclean all miniRT
