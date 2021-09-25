/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlink <mlink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:11:15 by mlink             #+#    #+#             */
/*   Updated: 2021/09/25 19:00:11 by mlink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/libft.h"
# include "op.h"
# include <fcntl.h>

# define SRC_TYPE ".s"
# define TRGT_TYPE ".cor"


typedef struct			s_asm
{
	int					source_fd;
	// int					core_fd;
	char				*file;
	char				*champ_name;
	char				*champ_comment;
	int					byte_size;
	int					line_cnt;
}						t_asm;

typedef struct			s_operation
{
	char				*label;
	char				*op_name;
	// int					op_code;
	char				*arg[3];
	// int					argtypes[3];
	// int					op_size;
	// int					t_dir_size;
	// int					arg_type_code;
	// int					position;
	// int					label_pos[3];
	int					line;//
	struct s_operation	*next;
}						t_operation;


void		ft_error(char *str);
void		ft_error_whit_help(char *str);
void		print_help();
void		ft_error_with_line(char *str, char *line);

char		*save_name_comment(t_asm **core, char *line);

int				is_hex(char *argum);
int				ft_chrpos(char *str, char c);

void		read_file(t_asm **core, t_operation **list);
char	*reformat(char *line);
void		init_asm(char *filename, t_asm **core);
int				list_append(t_operation **head);
void		save_label_op(t_operation **list, t_operation *new, char *line, int *i);
void		get_args(t_operation *new, char *line);
void	lex_parser(t_asm **core, t_operation **list, char *line);
#endif