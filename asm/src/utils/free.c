/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 04:36:19 by katyaprusak       #+#    #+#             */
/*   Updated: 2022/01/12 20:06:50 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_t_asm_struct(void *object)
{
	if (((t_asm*)object)->source_fd > 2)
		if (close(((t_asm*)object)->source_fd) < 0)
			ft_error("Failed to close source file");
	if (((t_asm*)object)->target_fd > 2)
		if (close(((t_asm*)object)->target_fd) < 0)
			ft_error("Failed to close target file");
	if (((t_asm*)object)->champ_name)
		free(((t_asm*)object)->champ_name);
	if (((t_asm*)object)->champ_comment)
		free(((t_asm*)object)->champ_comment);
	if (((t_asm*)object)->file)
		free(((t_asm*)object)->file);
	free(object);
}

void	free_list(t_operation *list)
{
	t_operation *temp;
	t_operation *temp2;
	t_operation *temp3;

	temp = list;
	while (temp)
	{
		if (temp->label)
			free(temp->label);
		if (temp->op_name)
			free(temp->op_name);
		if (temp->arg[0])
			free(temp->arg[0]);
		if (temp->arg[1])
			free(temp->arg[1]);
		if (temp->arg[2])
			free(temp->arg[2]);
		temp2 = temp;
		temp3 = temp->next;
		free(temp2);
		temp = temp3;
	}
}
