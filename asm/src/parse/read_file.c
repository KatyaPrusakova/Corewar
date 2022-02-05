/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 18:37:35 by mlink             #+#    #+#             */
/*   Updated: 2022/02/04 15:48:29 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"

/*
** Checking if tmp is .name or .comment 
** In case of .name and .comment we save it in the header
** In other case, we need to parse it 
*/

void	read_validate_file(t_asm **core, t_operation **list)
{
	char	*line;
	char	*tmp;

	(*list) = NULL;
	line = NULL;
	while (get_next_line((*core)->source_fd, &line) > 0)
	{
		tmp = line;
		(*core)->line_pos += 1;
		while ((*tmp == ' ' || *tmp == '\t') && *tmp != '\0')
			tmp++;
		if (ft_strnstr(tmp, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		{
			if ((*core)->champ_name)
				ft_error(ERR_MULT_NAME);
			(*core)->champ_name = save_name_comment(core, line);
		}
		else if (ft_strnstr(tmp, COMMENT_CMD_STRING, \
							ft_strlen(COMMENT_CMD_STRING)))
		{
			if ((*core)->champ_comment)
				ft_error(ERR_MULT_NAME);
			(*core)->champ_comment = save_name_comment(core, line);
		}
		else
			lex_parser(core, list, line);
		free(line);
	}
	validate_input(core, list);
}
