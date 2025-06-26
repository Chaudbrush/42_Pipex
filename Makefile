# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/21 08:22:31 by vloureir          #+#    #+#              #
#    Updated: 2025/06/24 16:18:16 by vloureir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef VERBOSE
MAKEFLAGS += --silent
endif

NAME := pipex

SRC := $(wildcard src/*.c)

OBJ := $(SRC:.c=.o)

CFLAGS := 
#-Wall -Wextra -Werror

CC := cc

RM := rm -f

RED := \033[1;30;41m

GREEN := \033[1;30;42m

OFF := \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./libft/
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -Llibft -lft
	@echo "$(GREEN) Pipex Created $(OFF)"

clean:
	$(RM) $(OBJ)
	$(MAKE) -C ./libft/ clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C ./libft/ fclean
	@echo "$(RED) Pipex Deleted $(OFF)"

re: fclean all