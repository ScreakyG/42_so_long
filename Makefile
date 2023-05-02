NAME = so_long
FLAGS = -Wall -Wextra -g
CC = gcc

# SOURCES

SRCS_DIR = src/
SRCS_FILES = so_long.c error.c map_check.c map_creation.c player_movement.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS_SRC = $(SRCS:.c=.o)

# LMX

MLX_DIR = minilibx-linux/
MLX_NAME = libmlx.a
MLX = $(MLX_DIR)$(MLX_NAME)

# LIBFT

LIBFT_DIR = libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_DIR)$(LIBFT_NAME)

%.o: %.c
		$(CC) $(FLAGS) -I/usr/include -Iminilibx-linux -O3 -c $< -o $@

all: $(MLX) $(LIBFT) $(NAME)

$(NAME): $(OBJS_SRC)
		$(CC) $(FLAGS) $(OBJS_SRC) -Lminilibx-linux -lmlx -L/usr/lib -L$(LIBFT_DIR) -lft -Iminilibx-linux -lXext -lX11 -lm -lz -o $(NAME)

$(MLX):
		@echo "Creating minilibx library"
		make -sC $(MLX_DIR)

$(LIBFT):
		@echo "Creating libft library"
		make -sC $(LIBFT_DIR)

clean:
		@echo "Cleaning .o files"
		@rm -rf $(OBJS_SRC)
		@make clean -sC $(MLX_DIR)
		@make clean -sC $(LIBFT_DIR)

fclean: clean
		@echo "Deleting program"
		@rm -rf $(NAME)
		@make fclean -sC $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
