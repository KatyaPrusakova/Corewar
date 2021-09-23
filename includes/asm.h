/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 13:31:52 by mlink             #+#    #+#             */
/*   Updated: 2021/09/23 20:05:39 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <sys/uio.h>
# include <sys/types.h>
# include "../libft/libft.h"
# include "../libft/ft_printf/includes/ft_printf.h"
# include "op.h"
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct			s_buff
{
	int						size;
	unsigned char			*input;
	unsigned char			argument_type;
	int						buff_slot;
    
}						t_buff;

#endif