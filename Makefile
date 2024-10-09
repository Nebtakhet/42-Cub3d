# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 13:35:06 by cesasanc          #+#    #+#              #
#    Updated: 2024/10/08 21:02:02 by cesasanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= Cub3d
CC 		= cc

FLAGS 	= -Wall -Wextra -Werror
MLX42 	= ./MLX42/build/libmlx42.a

SRC_DIR = ./
OBJ_DIR	= ./obj/
LIBFT	= ./libft/

FILES 	= main.c \
		map_init.c \
		win_init.c \
		colors.c \
		parse_map.c \
		parsing.c \
		textures.c \
		utils.c \
		render.c \
		hooks.c \

MLX42FLAGS = -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
INCLUDES = -I$(SRC_DIR) -I./include
		
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT)/libft.a:
	@make -C $(LIBFT)

$(MLX42): 
	@if [ ! -d "./MLX42" ]; then \
		git clone git@github.com:codam-coding-college/MLX42.git MLX42; \
	fi
	@if [ ! -f "$(MLX42)" ]; then \
		cd MLX42 && cmake -B build && cmake --build build -j4; \
	fi

$(NAME): $(MLX42) $(LIBFT)/libft.a $(OBJ_FILES) 
	@echo "Compiling Cub3d..."
	@ $(CC) $(FLAGS) -o $(NAME) $(OBJ_FILES) -L$(LIBFT) -lft $(MLX42) $(MLX42FLAGS)
	@echo "\033[32m Cub3d has been built successfully!\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)Cub3d.h | $(OBJ_DIR)
	@echo "Compiling $< to $@"
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

fsanitize: $(MLX42) $(LIBFT)/libft.a $(OBJ_FILES)
	@ $(CC) $(FLAGS) -o $(NAME) $(OBJ_FILES) -L$(LIBFT) -lft $(MLX42) $(MLX42FLAGS) \
		-g -fsanitize=address -static-libasan
	
clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJ_DIR) $(OBJ_FILES:.o=.dSYM)
	
fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
