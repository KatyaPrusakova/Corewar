/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:11:15 by mlink             #+#    #+#             */
/*   Updated: 2022/01/12 20:09:26 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/libft.h"
# include "op.h"
# include "oplist_asm.h"
# include <fcntl.h>
// delete
# include <stdio.h>

# define SRC_TYPE ".s"
# define TRGT_TYPE ".cor"

/*
	s_asm is a structure that contains all the necessary information
	required to assemble a file. It contains the file name, the file
	descriptor, the number of lines, the number of bytes, the number
	champion name, source_fd is the file descriptor of the source file.
*/

typedef struct			s_asm
{
	int					source_fd;
	int					target_fd; // core fd

	char				*file; // target_file
	char				*champ_name;
	char				*champ_comment;
	int					byte_size;
	int					line_pos; // rename from line_cnt
}						t_asm;

/*
	s_operation is a structure that contains all the necessary information
	required for an operation. It contains the operation n
*/
typedef struct			s_operation
{
	char				*label;
	char				*op_name;
	int					op_code; // used during validation, check_further function
	char				*arg[3];
	int					argtypes[3]; // used during validation, check_further function 
	int					op_size; 
	int					t_dir_size;
	int					arg_type_code; // used during validation, check_further function
	int					position;
	int					label_pos[3]; // storing position of the label (identified after ":") 
	int					line;//
	struct s_operation	*next;
}						t_operation;

#define SwapByte4(ldata) \
   (((ldata & 0x000000FF) << 24) | \
   ((ldata & 0x0000FF00) << 8) | \
   ((ldata & 0x00FF0000) >> 8) | \
   ((ldata & 0xFF000000) >> 24))

#define 	SwapByte2(ldata) \
	(((ldata & 0x00FF) << 8) | \
	((ldata & 0xFF00) >> 8))


void		ft_error(char *str);
void		ft_error_whit_help(char *str);
void		print_help();
void		ft_error_with_line(char *str, char *line);

char		*save_name_comment(t_asm **core, char *line);

int				is_hex(char *argum);


void		read_validate_file(t_asm **core, t_operation **list);
char		*reformat(char *line);
void		init_asm(char *filename, t_asm **core);
int			list_append(t_operation **head);
void		save_label_op(t_operation **list, t_operation *new, char *line, int *i);
void		get_args(t_operation *new, char *line);
void		lex_parser(t_asm **core, t_operation **list, char *line);

void		validate_input(t_asm **core, t_operation **list);
int			special_arg_check(char *label, t_operation **head, int line);
int			check_label(char *label, t_operation **head);


int			get_byte_size(t_operation **list, t_asm **core);
int			get_next_label(char *label, t_operation **head, t_operation *cur, int pos);
int			find_position(t_operation **list, t_operation *temp, char *arg);

void		get_label_positions(t_operation **list);

void		get_special_args(t_operation **head);

void        print_struct(t_operation **list);

char		*x_to_deci(char *argum);

// compile

void	compile_to_bytecode(t_asm **core, t_operation *op);
void	write_magic_number(int fd);

// free
void	free_list(t_operation *list);
void	free_t_asm_struct(void *object);


void	validate_line(t_operation *operation, t_oplist ref);

void	write_exec_size(t_asm **core, int fd);
void	write_champ_name(t_asm **core, int fd);
void	write_champ_comment(t_asm **core, int fd);

void	write_exec_code(int target_fd, t_operation *op);

#endif