/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlink <mlink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:10:31 by mlink             #+#    #+#             */
/*   Updated: 2021/09/25 16:18:50 by mlink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"
#include "stdio.h" //remove

char	*filename_pars(const char *source, const char *src_type,\
		const char *target_type)
{
	char	*target;
	char	*base;

	target = NULL;
	// check if file ends on .s
	if (ft_str_end(source, src_type))
	{
		//taking name from file ex test.s -> test
		base = ft_strsub(source, 0, ft_strlen(source) - ft_strlen(src_type));
		// making it test.cor
		target = ft_strjoin(base, target_type);
		free(base);
	}
	return (target);
}

void		init_asm(char *filename, t_asm **core)
{
	if (!((*core) = (t_asm *)ft_memalloc(sizeof(t_asm))))
		ft_error(ERR_MALLOC_ASM);
	(*core)->file = filename_pars(filename, SRC_TYPE, TRGT_TYPE);
	if (!(*core)->file)
		ft_error(ERR_NAME);
	if (((*core)->source_fd = open(filename, O_RDONLY)) < 0)
		ft_error(ERR_OPEN);
	(*core)->byte_size = 0;
	(*core)->line_cnt = 0;
	(*core)->champ_name = NULL;
	(*core)->champ_comment = NULL;
}


// void	lex_parser(t_asm *core, t_operation **list, char *line)
// {
	// char	*reform;

	// if (!line || line[0] == '\0')
	// 	return ;
	// while (*line == ' ' || *line == '\t')
	// 	line = line + 1;
	// if (*line == '\0')
	// 	return ;
	// else if (*line == COMMENT_CHAR || *line == ALT_COMMENT_CHAR)
	// 	return ;
	// else if (!core->champ_name || !core->champ_comment || *line == '.')
	// {
	// 	if (*line == '.')
	// 		ft_dprintf(2, "Invalid command on line %d\n", core->line_cnt);
	// 	else
	// 		ft_dprintf(2, "Name or comment missing\n");
	// 	ft_error("Lexical error!");
	// }
	// reform = reformat(line);
	// list_append(list);
	// get_label_op(core, list, reform);
	// free(reform);
// }

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
	// 	else
	// 		lex_parser(core, list, line);
		free(line);
	}
	// do_checks(core, list);
}

int		main(int argc, char **argv)
{
	t_asm		*core;
	t_operation	*list;

	core = NULL;
	if (argc != 2)
		print_help();
	init_asm(argv[1], &core);
	list = NULL;
	read_file(&core, &list);
	// write_champion(core, list);
	// free_list(list);
	// clear_t_asm((void *)core);
	return (0);
}