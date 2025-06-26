# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/12 20:29:48 by vloureir          #+#    #+#              #
#    Updated: 2025/06/24 07:17:21 by vloureir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef VERBOSE
MAKEFLAGS += --silent
endif

NAME := libft.a

CC := cc

CFLAGS := -Wall -Wextra -Werror

SRC := ft_split.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c \
		ft_putstr_fd.c ft_putchar_fd.c env_split.c

OBJ := $(SRC:.c=.o)

INC := -Iincludes

HEADER := includes/libft.h

AR := ar -rcs

RM := rm -f

RED := \033[1;30;41m

GREEN := \033[1;30;42m

OFF := \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $^
	@echo "$(GREEN) Library Crated $(OFF)"

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME)
	@echo "$(RED) Library Deleted $(OFF)"

re: fclean all
