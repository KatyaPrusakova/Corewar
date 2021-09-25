/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlink <mlink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 18:37:35 by mlink             #+#    #+#             */
/*   Updated: 2021/09/25 18:38:09 by mlink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"

void	read_file(t_asm **core, t_operation **list)
{
	char	*line;
	char	*tmp;
	(*list) = NULL;
	(*core)->line_cnt = (*core)->line_cnt;

	line = NULL;
	while (get_next_line((*core)->source_fd, &line) > 0)
	{
		tmp = line;
		(*core)->line_cnt += 1;
		while ((*tmp == ' ' || *tmp == '\t') && *tmp != '\0')
			tmp++;
		if (ft_strnstr(tmp, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		{

			((*core)->champ_name) ? ft_error(ERR_MULT_NAME) : 0;
			(*core)->champ_name = save_name_comment(core, line);
		}
		else if (ft_strnstr(tmp, COMMENT_CMD_STRING, \
							ft_strlen(COMMENT_CMD_STRING)))
		{
			((*core)->champ_comment) ? ft_error(ERR_MULT_NAME) : 0;
			(*core)->champ_comment = save_name_comment(core, line);
		}
		else
			lex_parser(core, list, line);
		free(line);
	}
	// do_checks(core, list);
}