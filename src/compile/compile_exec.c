/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 19:48:41 by katyaprusak       #+#    #+#             */
/*   Updated: 2021/12/28 19:56:23 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "asm.h"

int		swap_int16(int val)
{
	return ((val & 0x00FF) << 8 | (val & 0xFF00) >> 8);
}

/*
** Write T_REG argument to .cor
*/

static void	write_t_reg(char *arg, int fd)
{
	int val;

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
		val = swap_int16(val);
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
	val = swap_int16(val);
	write(fd, &val, 2);
}

/*
** Cycle through arguments and write them to .cor
*/

static void	write_args_to_bytecode(t_operation *op, int fd)
{
	int cnt;

	cnt = 0;
	while (cnt < 3)
	{
		if (op->argtypes[cnt] == T_REG)
			write_t_reg(op->arg[cnt], fd);
		else if (op->argtypes[cnt] == T_DIR)
			write_t_dir(op->arg[cnt], op->t_dir_size, op->label_pos[cnt], fd);
		else if (op->argtypes[cnt] == T_IND)
			write_t_ind(op->arg[cnt], op->label_pos[cnt], fd);
		cnt += 1;
	}
}

int		get_arg_code(t_operation *operation)
{
	int cnt;
	int shift;
	int	ret;

	cnt = 0;
	shift = 6;
	ret = 0b00000000;
	while (cnt < 3)
	{
		if (operation->argtypes[cnt] == T_REG)
			ret += T_REG_CODE << shift;
		else if (operation->argtypes[cnt] == T_DIR)
			ret += T_DIR_CODE << shift;
		else if (operation->argtypes[cnt] == T_IND)
			ret += T_IND_CODE << shift;
		shift -= 2;
		cnt += 1;
	}
	return (ret);
}

/*
** Write champs exec code to .cor
*/

void		write_exec_code(int target_fd, t_operation *op)
{
	t_operation	*cpy;
	int			arg_code;

	cpy = op;
	while (cpy)
	{
		if (cpy->op_code)
		{
			write(target_fd, &cpy->op_code, 1);
			if (cpy->arg_type_code)
			{
				arg_code = get_arg_code(cpy);
				write(target_fd, &arg_code, 1);
			}
			write_args_to_bytecode(cpy, target_fd);
		}
		cpy = cpy->next;
	}
}
