/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_to_bytecode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 04:26:12 by katyaprusak       #+#    #+#             */
/*   Updated: 2021/12/28 19:51:26 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_headers(t_asm **core)
{
	int fd;
	int x;

	x = 0;
	fd = (*core)->target_fd;
	printf("target_fd %d\n", (*core)->target_fd);
	write_magic_number(fd);
	write_champ_name(core, fd);
	write(fd, &x, 4);
	write_exec_size(core, fd);
	write_champ_comment(core, fd);
	write(fd, &x, 4);
}

void	compile_to_bytecode(t_asm **core, t_operation *op)
{

	(*core)->target_fd = open((*core)->file, O_RDWR | O_TRUNC | O_CREAT, 0600);
	if ((*core)->target_fd < 0)
		ft_error("Open Error on target file");
	write_headers(core);
	write_exec_code((*core)->target_fd, op);
	printf("Writing output program to: %s\n %s\n", (*core)->file, op->op_name);
}