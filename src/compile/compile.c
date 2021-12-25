/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 01:08:44 by katyaprusak       #+#    #+#             */
/*   Updated: 2021/12/25 01:59:14 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

/*
** Write magic number from COREWAR_EXEC_MAGIC const
*/

void	write_magic_number(int fd)
{
	int magic;

	magic = COREWAR_EXEC_MAGIC;
	// magic = swap_int32(magic);
	write(fd, &magic, 4);
}


/*
** Write champions executable code size in 4 bytes
*/

void	write_exec_size(t_asm *core, int fd)
{
	int size;

	size = core->byte_size;
	// size = swap_int32(size);
	write(fd, &size, 4);
}

/*
** Write champions name and fill the remaining PROG_NAME_LENGTH with 0's
*/

void	write_champ_name(t_asm *core, int fd)
{
	int		cnt;
	int		zero;
	char	*str;

	cnt = 0;
	zero = 0;
	str = core->champ_name;
	while (str[cnt] != '\0' && cnt < NAME_LENGTH)
	{
		write(fd, &str[cnt], 1);
		cnt += 1;
	}
	while (cnt < NAME_LENGTH)
	{
		write(fd, &zero, 1);
		cnt += 1;
	}
}

/*
** Write champions comment and fill the remaining COMMENT_LENGTH with 0's
*/

void	write_champ_comment(t_asm *core, int fd)
{
	int		cnt;
	int		zero;
	char	*str;

	cnt = 0;
	zero = 0;
	str = core->champ_comment;
	while (str[cnt] != '\0' && cnt < COMMENT_LENGTH)
	{
		write(fd, &str[cnt], 1);
		cnt += 1;
	}
	while (cnt < COMMENT_LENGTH)
	{
		write(fd, &zero, 1);
		cnt += 1;
	}
}