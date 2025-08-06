MAKEFLAGS += --no-print-directory

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

SRC_DIR 	= source
OBJ_DIR 	= objects
LIB_DIR 	= library

LIBFT_DIR	= $(LIB_DIR)/libft
GNL_DIR		= $(LIB_DIR)/gnl
UTILS		= $(SRC_DIR)/utils
LEXICAL		= $(SRC_DIR)/lexical_analysis
SYNTAX		= $(SRC_DIR)/syntax_analysis
PARSER		= $(SRC_DIR)/parser
BUILTIN		= $(SRC_DIR)/builtin
ENV			= $(SRC_DIR)/environment
EXECUTION	= $(SRC_DIR)/execution

INCLUDES = -Iincludes -I$(LIBFT_DIR) -I$(GNL_DIR)

SRCS = \
	$(GNL_DIR)/get_next_line.c \
	$(GNL_DIR)/get_next_line_utils.c \
	$(UTILS)/simple_free_functions.c \
	$(UTILS)/compound_free_functions.c \
	$(UTILS)/env_utils.c \
	$(UTILS)/execution_utils.c \
	$(UTILS)/tokens_managing_utils.c \
	$(UTILS)/tokenizer_utils.c \
	$(UTILS)/builtin_utils.c \
	$(LEXICAL)/tokenizer.c \
	$(LEXICAL)/readline.c \
	$(LEXICAL)/init.c \
	$(LEXICAL)/token_quoted.c \
	$(SYNTAX)/strict_errors.c \
	$(SYNTAX)/secondary_errors.c \
	$(SYNTAX)/syntax.c \
	$(SYNTAX)/quotes_handle.c \
	$(SYNTAX)/heredoc_utils.c \
	$(SYNTAX)/heredoc.c \
	$(SYNTAX)/exit_status.c \
	$(PARSER)/ast_logic.c \
	$(PARSER)/ast_redirection.c \
	$(PARSER)/ast_parenthesis.c \
	$(BUILTIN)/shlvl.c \
	$(BUILTIN)/builtins.c \
	$(BUILTIN)/export_builtin.c \
	$(BUILTIN)/unset_builtin.c \
	$(BUILTIN)/env_builtin.c \
	$(BUILTIN)/pwd_builtin.c \
	$(BUILTIN)/cd_builtin.c \
	$(BUILTIN)/echo_builtin.c \
	$(BUILTIN)/exit_builtin.c \
	$(BUILTIN)/history.c \
	$(ENV)/env_init_utils.c \
	$(ENV)/env_init.c \
	$(EXECUTION)/execute_ast.c \
	$(EXECUTION)/execute_pipe.c \
	$(EXECUTION)/execute_redirs.c \
	$(EXECUTION)/execute_command.c \
	$(EXECUTION)/execute_command_no_fork.c \
	$(EXECUTION)/execute_convert.c \
	$(EXECUTION)/execute_cmd_path.c \
	$(EXECUTION)/wildcard.c \
	$(EXECUTION)/wildcard_utils.c \
	$(EXECUTION)/signals.c \
	$(SRC_DIR)/main.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBS = -lreadline

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a Makefile
	@echo Linking $(NAME)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT_DIR)/libft.a $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo Compiling $<
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT_DIR)/libft.a:
	@$(MAKE) -C $(LIBFT_DIR) bonus

all: $(NAME)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
