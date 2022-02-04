/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_special_args.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 04:13:03 by katyaprusak       #+#    #+#             */
/*   Updated: 2022/02/04 14:45:07 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	get_next_number(char *label, int i)
{
	int			num;
	char		c;
	static char	hexmask[] = "0123456789abcdefABCDEF";

	if (label[0] == '0' && (label[1] == 'x' || label[1] == 'X'))
	{
		i = 2;
		while (ft_str_char(hexmask, label[i]) >= 0)
			i = i + 1;
		c = label[i];
		label[i] = '\0';
		num = ft_atoi(x_to_deci(label));
		label[i] = c;
	}
	else
	{
		while (ft_isdigit(label[i]))
			i = i + 1;
		c = label[i];
		label[i] = '\0';
		num = ft_atoi(label);
		label[i] = c;
	}
	return (num);
}

void	assign_specials(t_operation *finder, int i, int total)
{
	if (finder->arg[i][0] == LABEL_CHAR)
		finder->label_pos[i] = total;
	else
	{
		free(finder->arg[i]);
		if (finder->arg[i][0] == DIRECT_CHAR)
			finder->arg[i] = ft_strjoin("%", ft_ultoa(total));
		else
			finder->arg[i] = ft_ultoa(total);
	}
}

int     get_total(t_operation **head, t_operation *cur, char *label)
{
    int total;

    total = 0;
    if (label[0] == DIRECT_CHAR) 
        label += 1;
    if (label[0] == LABEL_CHAR)
        total += get_next_label(label, head, cur, 1);
    else
	    total += get_next_number(label, 0);
    return total;
}

/*
** Loop to check if arg need math
** check position with direct or indirect label
*/

int	arg_math(t_operation **head, t_operation *cur, char *label)
{
	int				i;
	int				sign;
	long long int	total;

	i = 0;
	sign = 1;
	total = get_total(head, cur, label);
	while (label[i])
	{
		(label[i] == '-') ? (sign = -1) : 0;
		(label[i + 1] == LABEL_CHAR) ? (total +=
		(sign * get_next_label(label, head, cur, i + 2))) :
		(total += (sign * get_next_number(label + i + 1, 0)));
		sign = 1;
		i += 1;
	}
	return (total);
}

void	get_special_args(t_operation **head)
{
	t_operation	*tmp;
	int			i;
	int			pos;
	int			total;

	tmp = *head;
    
	while (tmp)
	{
		i = 0;
		while (tmp->arg[i] && i < 3)
		{
            pos = get_position(tmp->arg[i][0]);
			// delete
			// printf("finder->arg[i][0]: %c, pos: %d\n", tmp->arg[i][0], pos);
			
			if ((ft_str_char(tmp->arg[i], '+') > pos) ||
				(ft_str_char(tmp->arg[i], '-') > pos))
			{
				total = arg_math(head, tmp, tmp->arg[i]);
				assign_specials(tmp, i, total);
			}
			i += 1;
		}
		tmp = tmp->next;
	}
}
