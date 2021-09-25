/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlink <mlink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:10:31 by mlink             #+#    #+#             */
/*   Updated: 2021/09/25 18:57:50 by mlink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"
#include "stdio.h" //remove

void		get_label_op(t_asm **core, t_operation **list, char *line)
{
	int			i;
	t_operation	*new;

	i = 0;
	new = *list;
	while (new->next)
		new = new->next;
	new->line = (*core)->line_cnt;
	while (line[i])
	{
		if (line[i] == SEPARATOR_CHAR)
		{
			save_label_op(list, new, line, &i);
			line = line + i + 1;
			i = 0;
			if (new->op_name)
				break ;
		}
		(line[i] != '\0') ? (i += 1) : 0;
	}
	if (new->op_name)
	{
		get_args(new, line);
		// check_operation(new, core);
	}
}

void	lex_parser(t_asm **core, t_operation **list, char *line)
{
	char	*reform;

	if (!line || line[0] == '\0')
		return ;
	while (*line == ' ' || *line == '\t')
		line = line + 1;
	if (*line == '\0')
		return ;
	else if (*line == COMMENT_CHAR || *line == ALT_COMMENT_CHAR)
		return ;
	else if (!(*core)->champ_name || !(*core)->champ_comment || *line == '.')
	{
		if (*line == '.')
			ft_error_with_line(ERR_INV_COM, line);
		else
			ft_error(ERR_NAME_COM);
	}
	reform = reformat(line);
	printf("%s\n", reform);
	list_append(list);
	get_label_op(core, list, reform);
	free(reform);
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