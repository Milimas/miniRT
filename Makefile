# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/04 11:54:50 by rouarrak          #+#    #+#              #
#    Updated: 2023/11/23 15:47:45 by aminebeihaq      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS += -Wall -Werror -Wextra -O3 #-fsanitize=address -g3


UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CFLAGS += -D LINUX
	LDFLAGS += -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz #-fsanitize=address -g3
	INCLUDES += -I/usr/include -Imlx_linux
endif
ifeq ($(UNAME_S),Darwin)
	CFLAGS += -I.
	INCLUDES += -Lmlx -lmlx -framework OpenGL -framework AppKit
endif

HEADERS +=	./includes/minirt.h 	\
			./includes/color.h		\
			./includes/elements.h	\
			./includes/image.h		\
			./includes/ray.h		\
			./includes/vector.h		\
			./includes/parsing.h	\
			./includes/lighting.h	\
			./includes/matrix.h		\

NAME = miniRT

BONUS = miniRT_bonus

LIBFT = libft.a
LIBFT_DIR = libft/

SRC =	main.c								\
		srcs/put_pixel.c					\
		srcs/image.c						\
		srcs/window.c						\
		srcs/render.c						\
		srcs/vector/cross_product.c			\
		srcs/vector/normalize_vector.c		\
		srcs/vector/vector_subtraction.c	\
		srcs/vector/vector_division.c		\
		srcs/vector/vector_magnitude.c		\
		srcs/vector/dot_product.c			\
		srcs/vector/vector_addition.c		\
        srcs/vector/vector_scale.c			\
		parser/element_check.c				\
		parser/file_check.c					\
		parser/fill_cylinder.c				\
		parser/fill_plane.c					\
		parser/fill_sphere.c				\
		parser/parsing.c					\
		parser/utils_gnrl.c					\
		parser/utils_pars.c					\
		gnl/get_next_line.c					\
		gnl/get_next_line_utils.c			\
        srcs/color/color.c					\
        srcs/intesection/cone.c				\
        srcs/intesection/cylinder.c			\
        srcs/intesection/light.c			\
        srcs/intesection/plane.c			\
        srcs/intesection/sphere.c			\
		srcs/intesection/intersect.c		\
        srcs/lighting/ambient.c				\
        srcs/lighting/diffuse.c				\
        srcs/lighting/specular.c			\
		srcs/lighting/apply_light.c			\
		srcs/lighting/shadow.c				\
        srcs/matrix/dir.c					\
        srcs/matrix/rotation.c				\
        srcs/ray/ray.c						\
		srcs/math/clamp.c					\
		srcs/math/solve_quadratic.c			\
		srcs/math/max.c						\
		srcs/texture_map/cylinder.c			\
		srcs/texture_map/cone.c				\
		srcs/texture_map/plane.c			\
		srcs/texture_map/sphere.c			\
		srcs/texture_map/checkerboard.c		\
		srcs/texture_map/local_axis.c		\
		srcs/debug/print.c					\
		srcs/debug/print_obj.c				\
		
OBJ = $(SRC:.c=.o)

%.o: %.c $(HEADERS)
	echo $(UNAME_P)
	$(CC) $(CFLAGS)  -c $< -o $@ 

all: $(NAME) # $(BONUS)

$(NAME): $(OBJ) $(LIBFT) $(HEADERS)
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
