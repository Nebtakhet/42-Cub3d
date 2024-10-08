# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 11:47:56 by mmeier            #+#    #+#              #
#    Updated: 2024/10/08 13:21:00 by cesasanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

SRC_DIR = ./
OBJ_DIR	= ./obj/
LIBFT	= ./libft/

FILES = main.c 

MLX42FLAGS = -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

INCLUDES = -I$(SRC_DIR) -I./include
		
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

NAME = libft.a

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)textures

$(NAME): $(OBJ_FILES) $(MLX42) $(LIBFT)
	make -C $(LIBFT) > /dev/null
	@echo "Compiling Cub3d..."
	$(CC) $(FLAGS) -o $(NAME) $(OBJ_FILES) -L$(LIBFT) $(MLX42) $(MLX42FLAGS)
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
	$(CC) -o $(NAME) $(OBJ_FILES) -L$(LIBFT) $(MLX42) $(MLX42FLAGS) -g -fsanitize=address -static-libsan
	
clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJ_DIR) $(OBJ_FILES:.o=.dSYM)
	rm -rf MLX42
	
fclean: clean
	make clean -C $(LIBFT)
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
