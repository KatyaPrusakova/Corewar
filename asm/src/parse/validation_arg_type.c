/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_arg_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:20:45 by katyaprusak       #+#    #+#             */
/*   Updated: 2021/12/29 19:43:58 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_special(char *arg, int func)
{
	int pos;

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

int		is_t_reg(char *arg)
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

int		is_t_ind(char *arg)
{
	int cnt;

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

int		is_t_dir(char *arg)
{
	int cnt;

	cnt = 1;
	if (arg[0] != DIRECT_CHAR)
		return (0);
	if (is_special(arg, 1))
		return (1);
	else if ((ft_isdigit(arg[1]) || (arg[1] == '-' &&
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

int		validate_argent(char *arg)
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

void	validate_line(t_operation *operation, t_oplist ref)
{
	int	i;
	int	ret;

	i = 0;
	
	while (i < ref.arg_cnt)
	{
		ret = validate_argent(operation->arg[i]);
		if ((ret | ref.arg_type[i]) == ref.arg_type[i] && ret != 0)
			operation->argtypes[i] = ret;
		else
			ft_error("Wrong argent type!");
		i += 1;
	}
	if (i < 3 && operation->arg[i])
		ft_error("Wrong argent number!");
	operation->arg_type_code = ref.arg_type_code;
	operation->op_code = ref.opcode;
}
