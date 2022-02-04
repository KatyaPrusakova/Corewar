# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/15 12:46:08 by mlink             #+#    #+#              #
#    Updated: 2022/02/04 14:52:15 by katyaprusak      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

SRC = main.c \
print.c \
utils/error.c utils/free.c utils/init.c utils/is_hex.c \
parse/get_arg.c parse/label_op.c parse/name_comment.c parse/read_file.c \
parse/validation_line.c \
parse/validation_special_args.c parse/validation_special_args_utils.c\
parse/validation.c parse/validation_labels.c parse/validation_utils.c parse/reduce_space.c \
parse/validation_line_arg.c \
compile/byte_size.c compile/compile.c \
compile/compile_to_bytecode.c \
compile/compile_exec.c \


SRC_DIR = src
OBJ_DIR = objects
SRCC = $(addprefix $(SRC_DIR)/, $(SRC))

FLAGS = -Wall -Wextra -Werror

HEADER = -I includes
LIBFT_HEADER = -I libft/includes

LIBFT = libft/libft.a

RESET = \033[0m
YELLOW = \033[0;33m
GREEN = \033[0;32m
BOLD_BLUE = \033[1;34m

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS) -c -g $(LIBFT_HEADER) $(HEADER) $< -o $@

$(NAME): $(SRCC)
	@echo "	$(GREEN)<<$(RESET)$(YELLOW)$(NAME) is compiling...$(GREEN)>>$(RESET)"
	@make -C libft
	@gcc $(FLAGS) -g -o $@ $^ $(LIBFT_HEADER) $(HEADER) $(LIBFT) $(BONUS)
	@echo "	$(GREEN)<<$(RESET)$(BOLD_BLUE)$(NAME) is ready to use$(GREEN)>>$(RESET)"

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@make -C libft clean
	@echo "	$(GREEN)<<$(RESET)$(YELLOW)all $(NAME) .o files $(GREEN)>>$(RESET)"

fclean:
	@/bin/rm -rf $(OBJ_DIR)
	@/bin/rm -f $(NAME)
	@make -C libft fclean
	@echo "	$(GREEN)<<$(RESET)$(YELLOW)$(NAME) deleted$(GREEN)>>$(RESET)"

re: fclean all

.PHONY: all clean fclean re