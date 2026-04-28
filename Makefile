NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC = read_file.c \
      parse_config.c \
      parse_config_utils.c \
      extract_map.c \
      main.c \
      validate_map.c \
      init_game.c \
      init_mlx.c image_utils.c keys.c raycasting.c render_3d.c \
	  textures.c minimap.c cleanup.c \
	  more_parsing_utils.c parsing_utils.c raycasting_utils.c \
	  textures_utils.c validate_map_utils.c keys_utils.c \
	  read_file_utils.c set_texture.c door.c minimap_utils.c \
	  cleanup_utils.c


OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

INCLUDES = -I$(LIBFT_DIR) -I$(MLX_DIR)
LDFLAGS = $(LIBFT) $(MLX) -lXext -lX11 -lm

GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RED = \033[0;31m
RESET = \033[0m

REPO = https://github.com/42paris/minilibx-linux.git

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@echo "$(BLUE)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) created!$(RESET)"

$(LIBFT):
	@echo "$(YELLOW)📚 Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory -s

$(MLX):
	@echo "$(YELLOW)🖼️  Compiling MiniLibX...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) --no-print-directory -s

mlx:
	git clone $(REPO)

%.o: %.c
	@echo "$(YELLOW)⚙️  Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)🧹 Cleaning objects...$(RESET)"
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory -s
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory -s

fclean: clean
	@echo "$(RED)🔥 Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory -s

re: fclean all

.PHONY: all clean fclean re