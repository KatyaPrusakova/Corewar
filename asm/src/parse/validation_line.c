/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:20:45 by katyaprusak       #+#    #+#             */
/*   Updated: 2022/02/04 14:50:31 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	validate_line(t_operation *operation, t_oplist ref)
{
	int	i;
	int	ret;

	i = 0;
	while (i < ref.arg_cnt)
	{
		ret = validate_arg(operation->arg[i]);
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
