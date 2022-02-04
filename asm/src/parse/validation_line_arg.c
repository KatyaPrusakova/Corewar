/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_line_arg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:20:45 by katyaprusak       #+#    #+#             */
/*   Updated: 2022/02/04 14:56:28 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	is_special(char *arg, int func)
{
	int	pos;

	pos = 0;
	if (arg[1] == LABEL_CHAR && func)
		return (1);
	else if (arg[0] == LABEL_CHAR && !func)
		return (1);
	else if (func)
		pos = 1;
	if (ft_str_char(arg, '+') > pos || ft_str_char(arg, '-') > pos)
		return (1);
	else if (is_hex(arg))
		return (1);
	return (0);
}

int	is_t_reg(char *arg)
{
	int	reg_num;

	if (arg[0] != 'r')
		return (0);
	reg_num = ft_atoi(arg + 1);
	if (reg_num > 99 || reg_num < 0)
		return (0);
	else
		return (1);
}

int	is_t_ind(char *arg)
{
	int	cnt;

	cnt = 0;
	if (arg[0] == DIRECT_CHAR)
		return (0);
	if (is_special(arg, 0))
		return (1);
	else if (ft_isdigit(arg[0]) || (arg[0] == '-' && ft_isdigit(arg[1])))
	{
		if (arg[0] == '-')
			cnt = cnt + 1;
		while (arg[cnt] != '\0')
		{
			if (!ft_isdigit(arg[cnt]))
				return (0);
			cnt += 1;
		}
		return (1);
	}
	return (0);
}

int	is_t_dir(char *arg)
{
	int	cnt;

	cnt = 1;
	if (arg[0] != DIRECT_CHAR)
		return (0);
	if (is_special(arg, 1))
		return (1);
	else if ((ft_isdigit(arg[1]) || (arg[1] == '-' && \
		ft_isdigit(arg[2]))) && (arg[2] != 'x' && arg[2] != 'X'))
	{
		if (arg[1] == '-')
			cnt = cnt + 1;
		while (arg[cnt] != '\0')
		{
			if (!ft_isdigit(arg[cnt]))
				return (0);
			cnt += 1;
		}
		return (1);
	}
	return (0);
}

int	validate_arg(char *arg)
{
	if (!arg)
		ft_error("No argent provided!");
	if (is_t_reg(arg))
		return (T_REG);
	else if (is_t_ind(arg))
		return (T_IND);
	else if (is_t_dir(arg))
		return (T_DIR);
	ft_error("Invalid argent provided!");
	return (0);
}
