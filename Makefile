# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 11:47:56 by mmeier            #+#    #+#              #
#    Updated: 2024/10/07 12:10:25 by cesasanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3d
CC = cc
FLAGS = -Wall -Wextra -Werror
MLX42 = ./MLX42/build/libmlx42.a

SRC_DIR = ./
OBJ_DIR = ./obj/

FILES = main.c 

MLX42FLAGS = -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

INCLUDES = -I$(SRC_DIR) -I./include
		
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))


all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_FILES) $(MLX42)
	@echo "Compiling Cub3d..."
	$(CC) $(FLAGS) -o $(NAME) $(OBJ_FILES) $(MLX42) $(MLX42FLAGS)
	@echo "\033[32m Cub3d has been built successfully!\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)Cub3d.h | $(OBJ_DIR)
	@echo "Compiling $< to $@"
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(MLX42): 
	@if [ ! -d "./MLX42" ]; then \
		git clone git@github.com:codam-coding-college/MLX42.git MLX42; \
	fi
	@if [ ! -f "$(MLX42)" ]; then \
		cd MLX42 && cmake -B build && cmake --build build -j4; \
	fi

fsanitize: 
	$(CC) -o $(NAME) $(OBJ_FILES) $(MLX42) $(MLX42FLAGS) -g -fsanitize=address -static-libsan
	
clean:
	rm -rf $(OBJ_DIR) $(OBJ_FILES:.o=.dSYM)
	rm -rf MLX42
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re