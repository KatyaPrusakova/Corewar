/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_labels.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 03:54:08 by katyaprusak       #+#    #+#             */
/*   Updated: 2021/12/25 00:52:37 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int				ft_chrpos(char *str, char c)
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


/*
** Go through the linked list to find labels
*/

void	get_label_positions(t_operation **list)
{
	t_operation	*temp;
	int			i;
	int			pos;

	temp = *list;
	while (temp)
	{
		i = 0;
		pos = 0;
		if (temp->op_name)
		{
			while (temp->arg[i] && i < 3)
			{
				if ((pos = ft_chrpos(temp->arg[i], LABEL_CHAR)) >= 0) {
                    
					temp->label_pos[i] = find_position(list, temp, \
					temp->arg[i] + pos + 1);
                }
                // printf("get_label_positions temp->arg: %s %s %s\n ", temp->arg[0],  temp->arg[1],  temp->arg[2]);
				i = i + 1;
			}
		}
		temp = temp->next;
	}
}
