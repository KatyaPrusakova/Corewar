/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:32:35 by katyaprusak       #+#    #+#             */
/*   Updated: 2021/12/20 03:26:04 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "asm.h"
#include "error.h"

static void     validate_chars(char *label)
{
	int i;

	i = 0;
	while (label[i])
	{
		if (!ft_strchr(LABEL_CHARS, label[i]))
		{
			ft_error("Invalid char used in label!");
		}
		i += 1;
	}
}

/*
** Checks the label by running through the list.
*/

int		check_label(char *label, t_operation **head)
{
	t_operation *cpy;

	cpy = *head;
    printf("function check_label %s\n", label);
    validate_chars(label);
	while (cpy)
	{
		if (cpy->label)
		{
			if (ft_strequ(label, cpy->label)) {
                // delete
                printf("cpy->label: %s\n", cpy->label);
				return (1);
            }
		}
		cpy = cpy->next;
	}
    // printf("Invalid label: \"%s\" on line %d\n", label, line);
	// ft_error("Wrong chars in label!");
	return (0);
}


/*
** checks if label is valid
** if not valid returns 0
*/

int		verify_label(char *label, t_operation **head, int *i)
{
	char	*temp;
	int		start;

	start = 0;
    printf("function verify_label\n");
	if (label[*i] == LABEL_CHAR)
	{
		start = *i + 1;
		while (label[*i] != '+' && label[*i] != '-' && label[*i])
			*i = *i + 1;
		temp = ft_strsub(label, start, *i - start);
		if (!check_label(temp, head))
		{
			free(temp);
			return (0);
		}
		free(temp);
	}
	return (1);
}

int		verify_hex(char *label, int *i)
{
	static char hexmask[] = "0123456789abcdefABCDEF";

    //delete
    printf("function verify_hex\n");
	if (label[*i] == '0' && (label[*i + 1] == 'x' || label[*i + 1] == 'X'))
	{
		*i = *i + 2;
		if (label[*i])
		{
			while (ft_strchr(hexmask, label[*i]) >= 0)
				*i = *i + 1;
			if (label[*i] != '\0' && label[*i] != '+' && label[*i] != '-')
				return (0);
		}
		else
			return (0);
	}
	return (1);
}

int		verify_digit(char *label, int *i)
{
    printf("function verify_digit\n");
	if (ft_isdigit(label[*i]))
	{
		while (ft_isdigit(label[*i]))
			*i = *i + 1;
		if (label[*i] != '\0' && label[*i] != '+' && label[*i] != '-')
			return (0);
	}
	return (1);
}

int		check_math_errors(char *label, int line, int *i)
{
	if (label[*i] == '-' || label[*i] == '+')
	{
		*i = *i + 1;
		if (label[*i] == '\0')
		{
			printf( "Arg math error on line %d\n", line);
			ft_error("Extra +/- at the end!");
		}
	}
	else if (label[*i] != '\0')
		return (0);
	if (label[*i] == '-' || label[*i] == '+')
	{
		printf( "Arg math error on line %d\n", line);
		ft_error("Multiple -/+ in math arg!");
	}
	return (1);
}

/*
** Checks if argument has format such as: :live -:l1 + 5 - 0xff
** Splits the arg into chunks and calls checks.
*/

int		special_arg_check(char *label, t_operation **head, int line)
{
	int i;

	i = 0;
	if (label[0] == DIRECT_CHAR)
		i = 1;
    // delete
    printf("function special_arg_check\n");
	while (label[i])
	{
		if (!verify_label(label, head, &i))
			return (0);
		else if (!verify_hex(label, &i))
			return (0);
		else if (!verify_digit(label, &i))
			return (0);
		if (!check_math_errors(label, line, &i))
			return (0);
	}
	return (1);
}
