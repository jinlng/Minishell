# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/14 12:34:16 by potabaga          #+#    #+#              #
#    Updated: 2026/01/28 13:59:22 by potabaga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT_DIR = ./libft
CFLAGS = -Wall -Wextra -Werror -MMD -MP -ggdb

SRCS = src/builtins.c \
		src/executor.c \
		src/parser.c \
		src/utils.c \
		src/path.c \
		src/signals.c \
		src/env.c \
		src/redir.c\
		src/input_redir.c \
		src/pipe.c \
		src/pipe_utils.c \
        src/main.c

OBJS = $(SRCS:%=%.o)
DEPS = $(OBJS:%.o=%.d)

INCLUDES = -Iincludes -I$(LIBFT_DIR)

all: $(NAME)

%.c.o: %.c
	cc $(CFLAGS) $(INCLUDES) $< -c -o $@

-include $(DEPS)

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a
	cc $(CFLAGS) $^ -o $@
READLINE = -lreadline

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a
	cc $(CFLAGS) $^ $(READLINE) -o $@

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR) all 

clean:
	$(MAKE) -C $(LIBFT_DIR) $@
	rm -f $(OBJS) $(DEPS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) $@
	rm -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all re fclean clean
