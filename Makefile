# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rserban <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/17 11:29:48 by rserban           #+#    #+#              #
#    Updated: 2015/03/04 18:49:46 by rserban          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1
SRC = rtv1.c ft_render.c ft_vector.c ft_utils.c ft_scene.c ft_scene2.c \
	  ft_intersect.c ft_vector_math.c ft_color.c read_file1.c
OBJ = $(SRC:.c=.o)
EXTRA = -L/usr/X11/lib -lmlx -lXext -lX11
ARG = -Wextra -Wall -Werror

all: $(NAME)

$(NAME):
	@cd libft && make
	@gcc $(ARG) -c $(SRC)
	@gcc -o $(NAME) $(OBJ) libft/libft.a $(EXTRA)

clean:
	@cd libft && make clean
	@/bin/rm -f $(OBJ)

fclean: clean
	@cd libft && make fclean
	@/bin/rm -f $(NAME)

re: fclean all
