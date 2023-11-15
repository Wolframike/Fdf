# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/20 17:19:47 by misargsy          #+#    #+#              #
#    Updated: 2023/10/24 17:54:57 by misargsy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror -fsanitize=address
MLXF = -framework OpenGL -framework AppKit

SRCS =	fdf_render.c \
		fdf_read.c \
		fdf_util.c \
		fdf.c

NAME = fdf
LIBFT = libft.a
MLX = libmlx.dylib

OBJS = $(SRCS:.c=.o)

CHECK		= \033[32m[✔]\033[0m
BLUE		= \033[1;34m
RESET		= \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo "$(BLUE)Compiling Fdf... $(RESET)"
	@cc $(FLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME) $(MLXF)
	@echo "$(CHECK) $(RESET)"
	@clear
	@make banner

$(LIBFT):
	@echo "$(BLUE)Compiling libft... $(RESET)"
	@make -C libft
	@mv libft/libft.a .
	@echo "$(CHECK) $(RESET)"

$(MLX):
	@echo "$(BLUE)Compiling MiliLibX... $(RESET)"
	@make -C minilibx
	@mv minilibx/libmlx.dylib .
	@echo "$(CHECK) $(RESET)"

%.o: %.c
	@cc $(FLAGS) -c $< -o $@

clean:
	@echo "$(BLUE)Removing objects and libraries... $(RESET)"
	@rm -f $(OBJS) $(LIBFT) $(MLX)
	@make clean -C libft
	@make clean -C minilibx
	@echo "$(CHECK) $(RESET)"

fclean: clean
	@echo "$(BLUE)Removing executables... $(RESET)"
	@rm -f $(NAME) $(LIBFT) $(MLX)
	@echo "$(CHECK) $(RESET)"

re:	fclean	all

banner:
	@cc $(FLAGS) fdf_banner.c -o banner
	@./banner
	@rm banner

.PHONY: all bonus clean fclean re banner
