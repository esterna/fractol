#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esterna <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/26 17:01:46 by esterna           #+#    #+#              #
#    Updated: 2017/10/21 21:00:47 by esterna          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CFLAGS = -Wall -Wextra -Werror -framework OpenGL -framework Appkit 

DEPS = libft/libft.a\
	   minilibx_macos_10.11/libmlx.a\
	   libftprintf/libftprintf.a

DEBUG = -g -fsanitize=address

FUNCTIONS = $(wildcard *.c)

all: $(NAME)

libs:
	@make -C libftprintf/
	@make -C libft/
	@make -C minilibx_macos_10.11/

debug:
	@gcc $(CFLAGS) $(DEBUG) -o $(NAME) $(FUNCTIONS) $(DEPS)

$(NAME): libs
	@gcc $(CFLAGS) -o $(NAME) $(FUNCTIONS) $(DEPS)

clean:
	@make -C libftprintf/ clean
	@make -C libft/ clean
	@make -C minilibx_macos_10.11/ clean

fclean: clean
	@make -C libftprintf/ fclean
	@make -C libft/ fclean
	@/bin/rm -f $(NAME)
	@/bin/rm -rf *.dSYM

d_clean:
	@/bin/rm -f $(NAME)
	@/bin/rm -rf *.dSYM

re: fclean all

d_re: d_clean debug
