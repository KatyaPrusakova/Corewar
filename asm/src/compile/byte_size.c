/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 00:37:57 by katyaprusak       #+#    #+#             */
/*   Updated: 2022/02/04 14:26:53 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Counts the size of one link.
*/

static int	count_bytes(t_operation *temp, int j)
{
	int	bytes;
	int	i;

	i = 0;
	bytes = 1;
	while (temp->arg[i] != NULL && i < 3)
	{
		if (temp->arg[i][0] == 'r')
			bytes = bytes + 1;
		else if (temp->arg[i][0] == DIRECT_CHAR)
			bytes = bytes + g_oplist[j].t_dir_size;
		else
			bytes = bytes + 2;
		i = i + 1;
	}
	if (g_oplist[j].arg_type_code)
		bytes = bytes + 1;
	return (bytes);
}

/*
** Finds out t_dir_sizes from g_oplist and counts positions and total size.
*/

int	get_byte_size(t_operation **list, t_asm **core)
{
	int			i;
	t_operation	*temp;

	temp = *list;
	while (temp)
	{
		if (temp->op_name)
		{
			i = 0;
			while (i < 16)
			{
				if (ft_strequ(temp->op_name, g_oplist[i].opname))
				{
					temp->t_dir_size = g_oplist[i].t_dir_size;
					break ;
				}
				i += 1;
			}
			temp->op_size = count_bytes(temp, i);
		}
		temp->position = (*core)->byte_size;
		(*core)->byte_size = (*core)->byte_size + temp->op_size;
		temp = temp->next;
	}
	return (0);
}

/*
	When label found, go through list to find the position 
	it's pointing to.
** Calculate how many bytes to move forward/backward, if not found, error.
*/

int	find_position(t_operation **list, t_operation *cur, char *arg)
{
	t_operation	*find;

	find = *list;
	while (find)
	{
		if (ft_strequ(find->label, arg))
			return (find->position - cur->position);
		find = find->next;
	}
	return (0);
}

/*
** Finds label ending position in argument and checks the byte position.
*/

int	get_next_label(char *label, t_operation **head, t_operation *cur, int pos)
{
	int		i;
	int		total;
	char	*temp;

	total = 0;
	i = pos;
	while (label[i] && label[i] != '+' && label[i] != '-')
		i = i + 1;
	temp = ft_strsub(label, pos, i - 1);
	total = find_position(head, cur, temp);
	free(temp);
	return (total);
}
