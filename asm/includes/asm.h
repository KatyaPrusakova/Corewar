/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 13:31:52 by mlink             #+#    #+#             */
/*   Updated: 2021/09/23 22:44:16 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <sys/uio.h>
# include <sys/types.h>
# include "../../libft/libft.h"
# include "../../libft/ft_printf/includes/ft_printf.h"
# include "op.h"
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct	s_buf
{
	char		*data;
	size_t		size;
	size_t		used;
}				t_buf;

t_buf			*buf_new(t_buf *buf, size_t s);

# define CHECK_MODE 0
# define PRINT_MODE 1
# define ERROR_MIN 0
# define ERROR_MAX 30
# define NO_FILE_ERR 0
# define SOURCE_ERR 1
# define MALLOC_ERR 2
# define SIZE_ERROR 3
# define OPEN_ERROR 4
# define FILE_ERROR 5
# define INST_ERROR 6
# define LEX_ERROR 7

#endif