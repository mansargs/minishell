MAKEFLAGS	+= --no-print-directory

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC_DIR = lexical_analysis/srcs

OBJ_DIR = obj

INC_DIR = lexical_analysis/includes

LIBFT_DIR = libft

SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/tokenizer.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/tokenizer_utils.c \
	$(SRC_DIR)/defective_operator.c \
	$(SRC_DIR)/token.c \


OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBS = -lreadline

INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a
	@echo Compiling $<
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT_DIR)/libft.a $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo Compiling $<
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT_DIR)/libft.a:
	@$(MAKE) -C $(LIBFT_DIR)

all: $(NAME)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
