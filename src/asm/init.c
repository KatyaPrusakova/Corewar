/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 18:47:28 by mlink             #+#    #+#             */
/*   Updated: 2021/09/29 16:32:18 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"
#include <stdio.h> // delete

/* 
** Функция инициализации переменных и проверки на наличие ошибок
** file_name - имя файла
** tab_labels - таблица меток
*/

static char	*filename_pars(const char *source, const char *src_type,\
		const char *target_type)
{
	char	*target;
	char	*base;

	
	target = NULL;
	// check if file ends on .s
	if (ft_str_end(source, src_type))
	{
		printf("%s\n", source);
		printf("%s\n", src_type);
		printf("%s\n", "file file file");
		//taking name from file ex test.s -> test
		base = ft_strsub(source, 0, ft_strlen(source) - ft_strlen(src_type));
		// making it test.cor
		target = ft_strjoin(base, target_type);
		free(base);
	}
	return (target);
}

/* 
	Function that initializes all variables in t_asm struct and 
	checks for errors.
*/

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

/*
	Function for initializing t_operation struct.
*/
	
static t_operation		*new_list(void)
{
	t_operation *new;

	if (!(new = (t_operation*)ft_memalloc(sizeof(t_operation))))
		ft_error(ERR_MALLOC_OPER);
	new->label = NULL; 
	new->op_name = NULL;
	new->arg[0] = NULL;
	new->arg[1] = NULL;
	new->arg[2] = NULL;
	// new->argtypes[0] = 0;
	// new->argtypes[1] = 0;
	// new->argtypes[2] = 0;
	// new->next = NULL;
	// new->op_size = 0;
	// new->t_dir_size = 0;
	// new->op_code = 0;
	// new->position = 0;
	// new->label_pos[0] = 0;
	// new->label_pos[1] = 0;
	// new->label_pos[2] = 0;
	return (new);
}

int				list_append(t_operation **head)
{
	t_operation *last;

	last = *head;
	if (*head == NULL)
	{
		*head = new_list();
		return (1);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_list();
	return (1);
}
