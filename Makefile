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

CC = cc

CFLAGS += -Wall -Werror -Wextra -fsanitize=address -g3


CFLAGS += -I.
INCLUDES += -Lmlx -lmlx -lm -framework OpenGL -framework AppKit -O3 -fsanitize=address -g3

HEADERS +=	./includes/minirt.h 	\
			./includes/color.h		\
			./includes/elements.h	\
			./includes/image.h		\
			./includes/ray.h		\
			./includes/vector.h		\
			./includes/parsing.h	\

NAME = miniRT

BONUS = miniRT_bonus

LIBFT = libft.a
LIBFT_DIR = libft/

SRC =	main.c								\
		srcs/color.c						\
		srcs/put_pixel.c					\
		srcs/image.c						\
		srcs/vector/cross_product.c			\
		srcs/vector/normalize_vector.c		\
		srcs/vector/vector_subtraction.c	\
		srcs/vector/vector_division.c		\
		srcs/vector/vector_magnitude.c		\
		srcs/vector/dot_product.c			\
		srcs/vector/vector_addition.c		\
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
