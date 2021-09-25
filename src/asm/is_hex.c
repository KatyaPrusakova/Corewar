/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlink <mlink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 18:10:23 by mlink             #+#    #+#             */
/*   Updated: 2021/09/25 18:10:47 by mlink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				ft_chrpos(char *str, char c)
{
	int i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i = i + 1;
	}
	return (-1);
}

int				is_hex(char *argum)
{
	int		i;
	char	*hexmask;

	hexmask = "0123456789abcdefABCDEF";
	if (argum[0] == DIRECT_CHAR)
		i = 3;
	else
		i = 2;
	if (argum[i - 2] == '0' && (argum[i - 1] == 'x' || argum[i - 1] == 'X'))
	{
		while (argum[i] != '\0')
		{
			if (ft_chrpos(hexmask, argum[i]) < 0)
				return (0);
			i = i + 1;
		}
		return (1);
	}
	return (0);
}