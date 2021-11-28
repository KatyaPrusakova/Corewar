/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 18:51:18 by mlink             #+#    #+#             */
/*   Updated: 2021/10/03 20:46:27 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"
#include <stdio.h>

/*
	
*/

static void	check_label_chars(char *label)
{
	int i;

	i = 0;
	while (label[i])
	{
		if (!ft_strchr(LABEL_CHARS, label[i]))
			ft_error_with_line(ERR_LEB_CHAR, label);
		i += 1;
	}
}

/*

*/
static void		check_dup_labels(t_operation **list, char *label)
{
	t_operation *current;

	current = *list;
	while (current->next)
	{
		if (ft_strequ(current->label, label))
			ft_error_with_line(ERR_LEB_DUB, label);
		current = current->next;
	}
}

static void	save_label(t_operation **list, t_operation *new, char *line)
{
	int pos;

	if (new->label != NULL)
	{
		pos = new->line;
		list_append(list);
		new = new->next;
		new->line = pos;
	}
	new->label = ft_strdup(line);
	check_label_chars(new->label);
	check_dup_labels(list, new->label);
}

void		save_label_op(t_operation **list, t_operation *new, \
			char *line, int *i)
{
	char	*tmp;

	if (line[*i] == SEPARATOR_CHAR && line[*i - 1] == LABEL_CHAR)
	{
		line[*i - 1] = '\0';
		save_label(list, new, line);
	}
	else if (line[*i] == SEPARATOR_CHAR && line[*i - 1] != LABEL_CHAR)
	{
		line[*i] = '\0';
		tmp = ft_strchr(line, LABEL_CHAR);
		if (tmp)
		{
			tmp[0] = '\0';
			tmp++;
			save_label(list, new, line);
			new->op_name = ft_strdup(tmp);
			
		}
		else
			new->op_name = ft_strdup(line);
			// printf("%s\n", new->op_name);
	}
}
