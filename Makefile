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
LIBDIR = libft

FILES = main.c colors.c parsing.c parse_map.c textures.c utils.c 

LIBSRC = libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c libft/ft_isascii.c libft/ft_isprint.c \
		 libft/ft_strlen.c libft/ft_memset.c libft/ft_bzero.c libft/ft_memcpy.c libft/ft_memmove.c \
		 libft/ft_strlcpy.c libft/ft_strlcat.c libft/ft_toupper.c libft/ft_tolower.c libft/ft_strchr.c \
		 libft/ft_strrchr.c libft/ft_strncmp.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_strnstr.c \
		 libft/ft_atoi.c libft/ft_calloc.c libft/ft_strdup.c libft/ft_substr.c libft/ft_strjoin.c \
		 libft/ft_strtrim.c libft/ft_split.c libft/ft_itoa.c libft/ft_strmapi.c libft/ft_striteri.c \
		 libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c \
		 libft/ft_printf.c libft/put_functions.c libft/put_functions2.c libft/ft_lstnew_bonus.c \
		 libft/ft_lstadd_front_bonus.c libft/ft_lstsize_bonus.c libft/ft_lstlast_bonus.c \
		 libft/ft_lstadd_back_bonus.c libft/ft_lstdelone_bonus.c libft/ft_lstclear_bonus.c \
		 libft/ft_lstiter_bonus.c libft/ft_lstmap_bonus.c libft/get_next_line.c libft/get_next_line_utils.c

MLX42FLAGS = -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

INCLUDES = -I$(SRC_DIR) -I./include
		
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

LIBO = $(LIBSRC:.c=.o)

LIB = libft/libft.a

all: $(NAME)

$(MLX42): 
	@if [ ! -d "./MLX42" ]; then \
		git clone git@github.com:codam-coding-college/MLX42.git MLX42; \
	fi
	@if [ ! -f "$(MLX42)" ]; then \
		cd MLX42 && cmake -B build && cmake --build build -j4; \
	fi

$(LIB): $(LIBO)
	$(MAKE) -C $(LIBDIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(MLX42) $(OBJ_FILES)  $(LIB)
	@echo "Compiling Cub3d..."
	$(CC) $(FLAGS) -o $(NAME) $(LIB) $(OBJ_FILES) $(MLX42) $(MLX42FLAGS)
	@echo "\033[32m Cub3d has been built successfully!\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)Cub3d.h | $(OBJ_DIR)
	@echo "Compiling $< to $@"
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@


fsanitize: 
	$(CC) -o $(NAME) $(OBJ_FILES) $(MLX42) $(MLX42FLAGS) -g -fsanitize=address -static-libsan
	
clean:
	rm -rf $(OBJ_DIR) $(OBJ_FILES:.o=.dSYM)
	$(MAKE) -C $(LIBDIR) clean
	rm -rf MLX42
	
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBDIR) fclean

re: fclean all

.PHONY: all clean fclean re