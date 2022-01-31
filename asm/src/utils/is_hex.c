/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 18:10:23 by mlink             #+#    #+#             */
/*   Updated: 2021/12/29 13:25:23 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				is_hex(char *argum)
{
	int		i;

	if (argum[0] == DIRECT_CHAR)
		i = 3;
	else
		i = 2;
	if (argum[i - 2] == '0' && (argum[i - 1] == 'x' || argum[i - 1] == 'X'))
	{
		while (argum[i] != '\0')
		{
			if (ft_str_char("0123456789abcdefABCDEF", argum[i]) < 0)
				return (0);
			i = i + 1;
		}
		return (1);
	}
	return (0);
}