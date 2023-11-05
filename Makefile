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
INCLUDES += -Lmlx -lmlx -framework OpenGL -framework AppKit -fsanitize=address -g3

NAME = miniRT

BONUS = miniRT_bonus

LIBFT = libft.a
LIBFT_DIR = libft/

SRC =	main.c				\
		srcs/color.c		\
		srcs/put_pixel.c	\
		srcs/image.c		\
		srcs/vector/cross_product.c			\
		srcs/vector/normalize_vector.c		\
		srcs/vector/vector_subtraction.c	\
		srcs/vector/vector_division.c		\
		srcs/vector/vector_magnitude.c		\
		srcs/vector/dot_product.c			\
		srcs/vector/vector_addition.c		\

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
