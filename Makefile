# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlink <mlink@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/15 12:46:08 by mlink             #+#    #+#              #
#    Updated: 2021/09/25 13:01:41 by mlink            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME_ASM = asm
NAME_VM = corewar

SRC_ASM = main.c

SRC_VM = main.c 

SRC_DIR_ASM = asm/
OBJ_DIR_ASM = objects/asm
SRCC_ASM = $(addprefix $(SRC_DIR_ASM)/, $(SRC_ASM))

SRC_DIR_VM = srs/vm
OBJ_DIR_VM = objects/vm
SRCC_VM = $(addprefix $(SRC_DIR_VM)/, $(SRC_VM))

FLAGS = -Wall -Wextra -Werror

HEADER = -I includes
LIBFT_HEADER = -I libft/includes

LIBFT = libft/libft.a

RESET = \033[0m
YELLOW = \033[0;33m
GREEN = \033[0;32m
BOLD_BLUE = \033[1;34m

all: $(NAME_ASM) $(NAME_VM)
asm: $(NAME_ASM)

$(OBJ_DIR_ASM)/%.o: $(SRC_DIR_ASM)%.c
	@/bin/mkdir -p $(OBJ_DIR_ASM)
	@gcc $(FLAGS) -c $(LIBFT_HEADER) $(HEADER) $< -o $@

$(NAME_ASM): $(SRCC_ASM)
	@echo "	$(GREEN)<<$(RESET)$(YELLOW)$(NAME_ASM) is compiling...$(GREEN)>>$(RESET)"
	@make -C libft
	@gcc $(FLAGS) -o $@ $^ $(LIBFT_HEADER) $(HEADER) $(LIBFT)
	@echo "	$(GREEN)<<$(RESET)$(YELLOW)$(NAME_ASM) is ready to use$(GREEN)>>$(RESET)"

$(OBJ_DIR_VM)/%.o: $(SRC_DIR_VM)%.c
	@/bin/mkdir -p $(OBJ_DIR_VM)
	@gcc $(FLAGS) -c $(LIBFT_HEADER) $(HEADER) $< -o $@

$(NAME_VM): $(SRCC_VM)
	@echo "	$(GREEN)<<$(RESET)$(YELLOW)$(NAME_VM) is compiling...$(GREEN)>>$(RESET)"
	@make -C libft
	@gcc $(FLAGS) -o $@ $^ $(LIBFT_HEADER) $(HEADER) $(LIBFT)
	@echo "	$(GREEN)<<$(RESET)$(YELLOW)$(NAME_VM) is ready to use$(GREEN)>>$(RESET)"

clean:
	@/bin/rm -rf $(OBJ_DIR_ASM)
	@/bin/rm -rf $(OBJ_DIR_VM)
	@make -C libft clean
	@echo "	$(GREEN)<<$(RESET)$(YELLOW)all $(NAME_ASM) .o files are deleted$(GREEN)>>$(RESET)"
	@echo "	$(GREEN)<<$(RESET)$(YELLOW)all $(NAME_VM) .o files are deleted$(GREEN)>>$(RESET)"

fclean:
	@/bin/rm -rf $(OBJ_DIR_ASM)
	@/bin/rm -f $(NAME_ASM)
	@/bin/rm -rf $(OBJ_DIR_VM)
	@/bin/rm -f $(NAME_VM)
	@make -C libft fclean
	@echo "	$(GREEN)<<$(RESET)$(YELLOW)$(NAME_ASM) deleted$(GREEN)>>$(RESET)"
	@echo "	$(GREEN)<<$(RESET)$(YELLOW)$(NAME_VM) deleted$(GREEN)>>$(RESET)"

re: fclean all

.PHONY: all clean fclean re