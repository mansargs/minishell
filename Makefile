MAKEFLAGS += --no-print-directory

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRC_DIR = source
OBJ_DIR = objects
LIB_DIR = library

LIBFT_DIR = $(LIB_DIR)/libft
GNL_DIR   = $(LIB_DIR)/gnl
LEXICAL   = $(SRC_DIR)/lexical_analysis
SYNTAX    = $(SRC_DIR)/syntax_analysis

INCLUDES = -Iincludes -I$(LIBFT_DIR) -I$(GNL_DIR)

SRCS = \
	$(GNL_DIR)/get_next_line.c \
	$(GNL_DIR)/get_next_line_utils.c \
	$(SRC_DIR)/main.c \
	$(LEXICAL)/tokenizer.c \
	$(LEXICAL)/init.c \
	$(LEXICAL)/tokenizer_utils.c \
	$(LEXICAL)/token_quoted.c \
	$(SYNTAX)/strict_errors.c \
	$(SYNTAX)/secondary_errors.c \
	$(SYNTAX)/syntax.c \
	$(SYNTAX)/heredoc.c \
	$(SYNTAX)/absent_operand.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBS = -lreadline

# Target rule
$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a
	@echo Linking $(NAME)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT_DIR)/libft.a $(LIBS) -o $(NAME)

# Rule to build .o files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo Compiling $<
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create object directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Build libft
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
