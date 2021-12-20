/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 18:57:30 by mlink             #+#    #+#             */
/*   Updated: 2021/12/20 04:19:53 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"

static void		argum_len(char *argum, int *len, int *i)
{
	if (argum[0] == DIRECT_CHAR)
	{
		*len = ft_strlen(argum) - 4;
		*i = 3;
	}
	else
	{
		*len = ft_strlen(argum) - 3;
		*i = 2;
	}
}

static unsigned long	ft_pow(int number, int power)
{
	unsigned long total;

	total = number;
	if (!power)
		return (1);
	else if (power == 1)
		return (number);
	else
	{
		while (power > 1)
		{
			total = total * number;
			power = power - 1;
		}
	}
	return (total);
}

char			*x_to_deci(char *argum)
{
	unsigned long	hex;
	int				len;
	int				val;
	int				i;

	hex = 0;
	val = 0;
	argum_len(argum, &len, &i);
	while (argum[i] != '\0')
	{
		if (argum[i] >= '0' && argum[i] <= '9')
			val = argum[i] - 48;
		else if (argum[i] >= 'a' && argum[i] <= 'f')
			val = argum[i] - 97 + 10;
		else if (argum[i] >= 'A' && argum[i] <= 'F')
			val = argum[i] - 65 + 10;
		hex = hex + (val * ft_pow(16, len));
		len = len - 1;
		i = i + 1;
	}
	return (ft_ultoa(hex));
}

static void		get_hex(t_operation *new, char *line, int i)
{
	char	*temp;
	char	*hex;

	temp = x_to_deci(line);
	hex = ft_strjoin("%", temp);
	new->arg[i] = ft_strdup(hex);
	free(temp);
	free(hex);
}

void		get_args(t_operation *new, char *line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == SEPARATOR_CHAR)
		{
			if (j > 2)
				ft_error_with_line(ERR_ARG, line);
			line[i] = '\0';
			if (is_hex(line))
				get_hex(new, line, j);
			else
				new->arg[j] = ft_strdup(line);
			line = line + i + 1;
			j += 1;
			i = -1;
		}
		i += 1;
	}
}
