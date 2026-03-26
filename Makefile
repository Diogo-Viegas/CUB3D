NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = read_file.c \
      parse_config.c \
      parse_config_utils.c \
      extract_map.c \
      main.c \
      validate_map.c

OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I$(LIBFT_DIR)

GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(BLUE)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) created!$(RESET)"

$(LIBFT):
	@echo "$(YELLOW)📚 Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory -s

%.o: %.c
	@echo "$(YELLOW)⚙️  Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)🧹 Cleaning objects...$(RESET)"
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory -s

fclean: clean
	@echo "$(RED)🔥 Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory -s

re: fclean all

.PHONY: all clean fclean re