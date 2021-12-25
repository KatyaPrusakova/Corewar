/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlink <mlink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:31:15 by mlink             #+#    #+#             */
/*   Updated: 2021/09/25 16:33:48 by mlink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_help()
{
	ft_putendl("USAGE:");
    ft_putendl("    	./asm <filename.s>");
	exit(1);
}

void		ft_error_whit_help(char *str)
{
	write(1, str, ft_strlen(str));
	print_help();
}

void		ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	exit(1);
}

void		ft_error_with_line(char *str, char *line)
{
	write(1, str, ft_strlen(str));
	write(1, "\"", 1);
	write(1, line, ft_strlen(line));
	write(1, "\"\n", 2);
	exit(1);
}
