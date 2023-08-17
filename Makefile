# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/04 11:54:50 by rouarrak          #+#    #+#              #
#    Updated: 2023/08/14 16:32:51 by abeihaqi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

CFLAGS += -Wall -Werror -Wextra #-fsanitize=address -g3

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CCFLAGS += -D LINUX
	LDFLAGS += -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
	INCLUDES += -I/usr/include -Imlx_linux
endif
ifeq ($(UNAME_S),Darwin)
	CCFLAGS += -D OSX
	LDFLAGS += Imlx
	INCLUDES += -Lmlx -lmlx -framework OpenGL - framework AppKit
endif

NAME = miniRT

BONUS = miniRT_bonus

LIBFT = libft.a
LIBFT_DIR = libft/

SRC =	main.c	\

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

all: $(NAME) # $(BONUS)

$(NAME): $(OBJ) $(LIBFT) ./includes/minirt.h
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(INCLUDES) $(LDFLAGS) -o $(NAME)

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
