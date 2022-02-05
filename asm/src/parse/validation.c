/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:42:45 by katyaprusak       #+#    #+#             */
/*   Updated: 2022/02/04 17:27:08 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"

void	norm_and_check_lastline(char *last)
{
	int	i;

	i = 0;
	while (last[i] == ' ' || last[i] == '\t')
		i += 1;
	if (last[i] != '\0' && last[i] != COMMENT_CHAR && \
		last[i] != ALT_COMMENT_CHAR)
		ft_error("File does not end with newline!");
	free(last);
}

void	check_lastline(int source_fd)
{
	char	temp[1];
	char	*last;
	int		i;

	i = -2;
	lseek(source_fd, -1, SEEK_END);
	read(source_fd, &temp, 1);
	while (temp[0] != '\n')
	{
		lseek(source_fd, i, SEEK_END);
		read(source_fd, &temp, 1);
		i -= 1;
	}
	i = (i + 2) * -1;
	last = (char *)malloc(sizeof(char) * i + 1);
	if (!(last))
		ft_error("Malloc error");
	read(source_fd, last, i);
	last[i] = '\0';
	norm_and_check_lastline(last);
}


int	check_plus_minus(char *str, int pos)
{
	if (ft_str_char(str, '+') > pos || \
				ft_str_char(str, '-') > pos)
		return (1);
	return (0);
}

void	validate_labels(t_operation **head, int i, int pos, int test)
{
	t_operation	*finder;

	finder = *head;
	while (finder)
	{
		i = 0;
		while (finder->arg[i] && i < 3)
		{
			if (finder->arg[i][0] == DIRECT_CHAR)
				pos = 1;
			pos = 0;
			if (check_plus_minus(finder->arg[i], pos))
				test = special_arg_check(finder->arg[i], head);
			else
			{
				if (finder->arg[i][pos] == LABEL_CHAR)
					test = check_label(finder->arg[i] + pos + 1, head);
			}
			if (!test)
				ft_error("Argument error!");
			i += 1;
		}
		finder = finder->next;
	}
}

void	validate_input(t_asm **core, t_operation **list)
{
	if ((*core)->champ_name == NULL)
		ft_error("Champ name is missing!");
	else if (ft_strlen((*core)->champ_name) > NAME_LENGTH)
		ft_error("Champ name is too long (128)");
	if ((*core)->champ_comment == NULL)
		ft_error("Champ comment is missing!");
	else if (ft_strlen((*core)->champ_comment) > COMMENT_LENGTH)
		ft_error("Champ comment is too long (2048)");
	check_lastline((*core)->source_fd);
	validate_labels(list, 0, 0, 1);
	get_byte_size(list, core);
	get_label_positions(list);
	get_special_args(list);
}
