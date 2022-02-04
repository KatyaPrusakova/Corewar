/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_to_bytecode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 04:26:12 by katyaprusak       #+#    #+#             */
/*   Updated: 2022/02/04 15:17:23 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_headers(t_asm **core)
{
	int	fd;
	int	x;

	x = 0;
	fd = (*core)->target_fd;
	write_magic_number(fd);
	write_champ_name(core, fd);
	write(fd, &x, 4);
	write_exec_size(core, fd);
	write_champ_comment(core, fd);
	write(fd, &x, 4);
}

/*
** Write champs exec code to .cor
*/

void	write_exec_code(int target_fd, t_operation *op)
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

void	compile_to_bytecode(t_asm **core, t_operation *op)
{
	(*core)->target_fd = open((*core)->file, O_RDWR | O_TRUNC | O_CREAT, 0600);
	if ((*core)->target_fd < 0)
		ft_error("Open Error on target file");
	write_headers(core);
	write_exec_code((*core)->target_fd, op);
}
