/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_special_args.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 04:13:03 by katyaprusak       #+#    #+#             */
/*   Updated: 2021/12/25 00:38:39 by katyaprusak      ###   ########.fr       */
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

int	get_next_number(char *label, int i)
{
	int			num;
	char		c;
	static char	hexmask[] = "0123456789abcdefABCDEF";

	if (label[0] == '0' && (label[1] == 'x' || label[1] == 'X'))
	{
		i = 2;
		while (ft_chrpos(hexmask, label[i]) >= 0)
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
    printf("before assign_specials: %s\n", finder->arg[i]);
	if (finder->arg[i][0] == LABEL_CHAR)
		finder->label_pos[i] = total;
	else
	{
		free(finder->arg[i]);
		if (finder->arg[i][0] == DIRECT_CHAR)
			finder->arg[i] = ft_strjoin("%", ft_ultoa(total));
		else
			finder->arg[i] = ft_ultoa(total);
        printf("after assign_specials: %s\n", finder->arg[i]);
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
	printf("label is LABEL_CHAR: %s %lld\n", label, total);
    
	while (label[i])
	{
        printf("label char: %c\n", label[i]);
		(label[i] == '-') ? (sign = -1) : 0;
		(label[i + 1] == LABEL_CHAR) ? (total +=
		(sign * get_next_label(label, head, cur, i + 2))) :
		(total += (sign * get_next_number(label + i + 1, 0)));
		sign = 1;
		i += 1;
	}
	return (total);
}

int         get_position(char arg)
{
    if (arg == DIRECT_CHAR) {
        return 1;  
    }
    return 0;
}


void		get_special_args(t_operation **head)
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
			
			if ((ft_chrpos(tmp->arg[i], '+') > pos) ||
				(ft_chrpos(tmp->arg[i], '-') > pos))
			{
				total = arg_math(head, tmp, tmp->arg[i]);
				assign_specials(tmp, i, total);
			}
			i += 1;
		}
		tmp = tmp->next;
	}
}
