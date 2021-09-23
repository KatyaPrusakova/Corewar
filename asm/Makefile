# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/23 19:56:11 by katyaprusak       #+#    #+#              #
#    Updated: 2021/09/23 22:53:09 by katyaprusak      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.phony = all clean fclean re rec

NAME = asm

SRCS = ./*.c

LIBFT = ../libft/libft.a

SRC_FILES = main.c
SRC_PATH = ./
SRC = $(addprefix $(SRC_PATH), $(SRC_FILES))

FLAGS = -Wall -Werror -Wextra

OBJ = $(patsubst %.c, %.o, $(SRC_FILES))

OS := $(shell uname)
ifeq ($(OS), Linux)
	CLR_CODE = "\\e["
endif

ifeq ($(OS), Darwin)
	CLR_CODE = "\\x1b["
endif

GREEN = $(CLR_CODE)1;32m
RESET = $(CLR_CODE)0m

MAKE = make --no-print-directory

$(NAME):
	@echo "Compiling 'libft.a'"
	@$(MAKE) -C ../libft
	@echo "$(GREEN)Done$(RESET)\n"
	@echo "Compiling 'asm'- executable"
	@gcc $(SRC) -I includes  $(LIBFT) -o $(NAME)
	@echo "$(GREEN)Done$(RESET)\n"

all: $(NAME)

clean:
	@echo "Removing '.o'- files"
	@$(MAKE) clean -C ../libft
	@rm -f $(OBJ)
	@echo "$(GREEN)Done$(RESET)\n"

fclean: clean
	@echo "Removing 'asm'- executable"
	@rm -f $(NAME)
	@$(MAKE) fclean -C ../libft
	@echo "$(GREEN)Done$(RESET)\n"

re:
	@$(MAKE) fclean
	@$(MAKE) re -C ../libft
	@echo "Compiling 'asm'- executable"
	@gcc $(SRC) $(LIBFT) -I includes  -o $(NAME)
	@echo "$(GREEN)Done$(RESET)\n"

rec:
	@echo "Removing 'asm'- executable"
	@rm -f $(NAME)
	@echo "$(GREEN)Done$(RESET)\n"
	@echo "Compiling 'asm'- executable"
	@gcc $(SRC) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)Done$(RESET)\n"