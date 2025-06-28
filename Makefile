# Project
NAME      := minishell

# Compiler
CC        := cc
CFLAGS    := -Wall -Wextra -Werror -g
LDFLAGS   := -L$(HOME)/.brew/opt/readline/lib
CPPFLAGS  := -Iinc -Ilibft -I$(HOME)/.brew/opt/readline/include
LDLIBS    := -lreadline -lhistory -Llibft -lft

# Sources
SRCS      := main.c \
			 src/tokenizer/parser.c \
			 src/tokenizer/utils.c \
			 src/tokenizer/clean_up.c \
			 src/tokenizer/lexer.c \
             src/tokenizer/token.c \
			 src/tokenizer/token_utils.c \
			 src/gc/simple_gc.c \
			 src/gc/gc_malloc.c \
			 src/gc/gc_tokenizer.c \
			 src/gc/gc_whitespace.c \

# Objects
OBJ_DIR   := obj
OBJS      := $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Libft
LIBFT_DIR := libft
LIBFT_LIB := $(LIBFT_DIR)/libft.a

# Rules
.PHONY: all clean fclean re

all: $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

leaks:
		@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

re: fclean all