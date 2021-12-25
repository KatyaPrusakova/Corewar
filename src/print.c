/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 20:37:25 by katyaprusak       #+#    #+#             */
/*   Updated: 2021/12/05 17:10:58 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"
#include "stdio.h" //remove



void        print_struct(t_operation **list)
{
    int i;
    t_operation	*new;

	i = 0;
	new = *list;
    while (new != NULL) {
            printf("label      %s\n", new->label);
            printf("op_name    %s\n", new->op_name);
            printf("arg         |%s| |%s| |%s|\n", new->arg[0], new->arg[1], new->arg[2]);
            printf("line       %d\n", new->line);
            printf("______\n");
		    new = new->next;
        }

}