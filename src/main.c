/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:10:31 by mlink             #+#    #+#             */
/*   Updated: 2021/12/25 02:00:59 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"


int		check_argument(char *argum, t_asm **core)
{
	if (!argum)
	{
		printf("Missing instruction on line %d\n", (*core)->line_pos);
		ft_error("No argument provided!");
	}
	// if (check_t_reg(argum) == 1)
	// 	return (T_REG);
	// else if (check_t_ind(argum) == 1)
	// 	return (T_IND);
	// else if (check_t_dir(argum) == 1)
	// 	return (T_DIR);

	printf("Invalid instruction: \"%s\" on line %d\n", \
				argum, (*core)->line_pos);
	ft_error("Invalid argument provided!");
	return (0);

}

void	check_further(t_operation *operation, t_oplist ref, t_asm **core)
{
	int	i;
	int	ret;

	i = 0;
	while (i < ref.arg_cnt)
	{
		ret = check_argument(operation->arg[i], core);
		if ((ret | ref.arg_type[i]) == ref.arg_type[i] && ret != 0)
			operation->argtypes[i] = ret;
		else
		{
			printf("Invalid argument: \"%s\" on line %d\n", \
						operation->arg[i], (*core)->line_pos);
			ft_error("Wrong argument type!");
		}
		i += 1;
	}
	if (i < 3 && operation->arg[i])
	{
		printf("Invalid arguments on line: %d\n", (*core)->line_pos);
		ft_error("Wrong argument number!");
	}
	operation->arg_type_code = ref.arg_type_code;
	operation->op_code = ref.opcode;
}

void	check_operation(t_operation *operation, t_asm **core)
{
	int cnt;

	cnt = 0;
	while (cnt < 16)
	{
		if (ft_strequ(operation->op_name, g_oplist[cnt].opname))
		{
			check_further(operation, g_oplist[cnt], core);
			break ;
		}
		cnt += 1;
	}
	if (cnt == 16)
	{
		printf("Invalid instruction: \"%s\" on line %d\n", \
					operation->op_name, (*core)->line_pos);
		ft_error("No operation found!");
	}
}


/*
	Function that checks if the file is correct and if it is, it saves it in the
	corresponding new t_operation struct. 
*/
void		get_label_op(t_asm **core, t_operation **list, char *line)
{
	int			i;
	t_operation	*new;

	i = 0;
	new = *list;
	while (new->next)
		new = new->next;
	new->line = (*core)->line_pos;
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
		check_operation(new, core);
	}
	
}

/*
	Function that checks if the file is correct and if it is, it saves it in the
	corresponding new t_operation struct. Lexer tries to determine if proper token have been detected.
	Gets the line and checks if it is a label or an operation.
	reform is the line separated by "," sign therefore it is divided into tokens.
*/

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
	// printf("reform %s \n", reform);
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
	read_validate_file(&core, &list);
	compile_to_bytecode(&core, list);
	free_list(list);
	// clear_t_asm((void *)core);
	return (0);
}