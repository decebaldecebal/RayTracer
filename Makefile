# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rserban <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/17 11:29:48 by rserban           #+#    #+#              #
#    Updated: 2015/03/08 12:59:33 by rserban          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = raytracer
SRC = main.c ft_render.c ft_render2.c ft_vector.c ft_utils.c ft_scene.c \
	  ft_scene2.c ft_intersect.c ft_vector_math.c ft_color.c ft_read_file.c \
	  ft_read_objects.c ft_read_utils.c ft_free.c
OBJ = $(SRC:.c=.o)
EXTRA = -L/usr/X11/lib -lmlx -lXext -lX11
ARG = -Wextra -Wall -Werror

all: $(NAME)

$(NAME):
	@cd libft && make
	@gcc $(ARG) -c $(SRC)
	@gcc -o $(NAME) $(OBJ) libft/libft.a $(EXTRA)

simple:
	@gcc -o $(NAME) $(SRC) libft/libft.a $(EXTRA)

clean:
	@cd libft && make clean
	@/bin/rm -f $(OBJ)

fclean: clean
	@cd libft && make fclean
	@/bin/rm -f $(NAME)

re: fclean all
