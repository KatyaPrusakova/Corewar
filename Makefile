# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/15 12:46:08 by mlink             #+#    #+#              #
#    Updated: 2021/12/20 04:38:48 by katyaprusak      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

SRC = main.c error.c name_comment.c is_hex.c read_file.c reduce_space.c \
init.c label_op.c get_arg.c print.c \
validation.c validation_utils.c validation_labels.c validation_special_args.c byte_size.c \
compile/compile_to_bytecode.c \
free/free.c \


SRC_DIR = src/asm
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
	@gcc $(FLAGS) -c $(LIBFT_HEADER) $(HEADER) $< -o $@

$(NAME): $(SRCC)
	@echo "	$(GREEN)<<$(RESET)$(YELLOW)$(NAME) is compiling...$(GREEN)>>$(RESET)"
	@make -C libft
	@gcc $(FLAGS) -o $@ $^ $(LIBFT_HEADER) $(HEADER) $(LIBFT) $(BONUS)
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