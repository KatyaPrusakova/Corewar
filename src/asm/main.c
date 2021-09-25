/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlink <mlink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:10:31 by mlink             #+#    #+#             */
/*   Updated: 2021/09/25 14:57:08 by mlink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"
#include "stdio.h"

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

void	save_name_comment(t_asm **core, char *line)
{
	char	*ret;
	int		i;
	int		pos_start;
	// char	*cntd;
	(*core)->line_cnt = (*core)->line_cnt;

	i = 0;
	// find champion's name start
	while (line[i] != '\"')
	{
		(line[i] == '\0') ? ft_error(ERR_NO_NAME) : 0;
		i += 1;
	}
	pos_start = i + 1;
	i += 1;
	while (line[i] != '\0' && line[i] != '\"')
		i += 1;
	if (line[i] == '\0')
	{
		ret = ft_strdup(&line[pos_start]);
		// cntd = continue_reading((*core)->source_fd);
		// ret = strjoin_first(ret, cntd);
		// free(cntd);
	}
	else
		ret = ft_strdup(&line[pos_start]);
	printf("%s'n", ret);
	// return (remove_trailing_spaces(ret));
}

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
		while ((*tmp == ' ' || *tmp == '\t') && *tmp != '\0') //is_space ft
			tmp++;
		if (ft_strnstr(tmp, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		{

			((*core)->champ_name) ? ft_error(ERR_MULT_NAME) : 0;
			save_name_comment(core, line); //core->champ_name save!!!
		}
	// 	else if (ft_strnstr(tmp, COMMENT_CMD_STRING, \
	// 						ft_strlen(COMMENT_CMD_STRING)))
	// 	{
	// 		(core->champ_comment) ? ft_error("Multiple comments!") : 0;
	// 		core->champ_comment = save_name_comment((*core)->source_fd, line);
	// 	}
	// 	else
	// 		lex_parser(core, list, line);
	// 	free(line);
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