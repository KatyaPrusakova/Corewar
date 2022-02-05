/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 19:48:41 by katyaprusak       #+#    #+#             */
/*   Updated: 2022/02/04 15:17:56 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Write T_REG argument to .cor
*/

static void	write_t_reg(char *arg, int fd)
{
	int	val;

	val = ft_atoi(arg + 1);
	write(fd, &val, 1);
}

/*
** Write T_DIR argument to .cor
*/

static void	write_t_dir(char *arg, int dir_size, int label_pos, int fd)
{
	int	val;

	if (arg[1] == LABEL_CHAR)
		val = label_pos;
	else
		val = ft_atoi(arg + 1);
	if (dir_size == 2)
		val = SwapByte2(val);
	else if (dir_size == 4)
		val = SwapByte4(val);
	write(fd, &val, dir_size);
}

/*
** Write T_IND argument to .cor
*/

static void	write_t_ind(char *arg, int label_pos, int fd)
{
	int	val;

	if (arg[0] == LABEL_CHAR)
		val = label_pos;
	else
		val = ft_atoi(arg);
	val = SwapByte2(val);
	write(fd, &val, 2);
}

/*
** Cycle through arguments and write them to .cor
*/

void	write_args_to_bytecode(t_operation *op, int fd)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (op->argtypes[i] == T_REG)
			write_t_reg(op->arg[i], fd);
		else if (op->argtypes[i] == T_DIR)
			write_t_dir(op->arg[i], op->t_dir_size, op->label_pos[i], fd);
		else if (op->argtypes[i] == T_IND)
			write_t_ind(op->arg[i], op->label_pos[i], fd);
		i += 1;
	}
}

int	get_arg_code(t_operation *operation)
{
	int	i;
	int	shift;
	int	ret;

	i = 0;
	shift = 6;
	ret = 0b00000000;
	while (i < 3)
	{
		if (operation->argtypes[i] == T_REG)
			ret += T_REG_CODE << shift;
		else if (operation->argtypes[i] == T_DIR)
			ret += T_DIR_CODE << shift;
		else if (operation->argtypes[i] == T_IND)
			ret += T_IND_CODE << shift;
		shift -= 2;
		i += 1;
	}
	return (ret);
}
