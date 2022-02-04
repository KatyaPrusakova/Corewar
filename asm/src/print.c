/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 20:37:25 by katyaprusak       #+#    #+#             */
/*   Updated: 2022/02/04 15:56:44 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"

void	print_struct(t_operation **list)
{
	int			i;
	t_operation	*new;

	i = 0;
	new = *list;
	while (new != NULL)
	{
		ft_printf("label  %s\n", new->label);
		ft_printf("op_name    %s\n", new->op_name);
		ft_printf("arg |%s| |%s| |%s|\n", new->arg[0], new->arg[1], new->arg[2]);
		ft_printf("line       %d\n", new->line);
		ft_printf("______\n");
		new = new->next;
	}
}
