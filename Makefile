# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinliang <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/14 12:34:16 by potabaga          #+#    #+#              #
#    Updated: 2026/02/13 16:48:48 by jinliang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -ggdb
INCLUDES = -I./includes -I./libft
LIBS = -L./libft -lft -lreadline
LIBFT = libft/libft.a

SRCS = $(shell find src -name "*.c")
# SRCS = src/builtins.c \
# 		src/builtin/cat.c \
# 		src/executor.c \
# 		src/expansion.c \
# 		src/lexer/lexer_tools.c \
# 		src/lexer/lexer.c \
# 		src/parser/cmd.c \
# 		src/parser/dollar.c \
# 		src/parser/parser.c \
# 		src/utils.c \
# 		src/path.c \
# 		src/signals.c \
# 		src/env.c \
# 		src/redir.c\
# 		src/input_redir.c \
# 		src/pipe.c \
# 		src/pipe_utils.c \
#         src/main.c

OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@printf "$(YELLOW)Linking $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@printf "$(GREEN)✓ $(NAME) created$(RESET)\n"

$(LIBFT):
	@printf "$(YELLOW)Compiling libft...$(RESET)\n"
	@make -s -C libft
	@printf "$(GREEN)✓ Libft ready$(RESET)\n"

%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -s -C libft clean
	@find . -name "*.d" -delete

fclean: clean
	@rm -f $(NAME)
	@make -s -C libft fclean

re: fclean
	$(MAKE) all

.PHONY: all re fclean clean
