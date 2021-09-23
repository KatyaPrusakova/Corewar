/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 19:32:33 by katyaprusak       #+#    #+#             */
/*   Updated: 2021/09/23 23:07:43 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../libft/ft_printf/includes/ft_printf.h"
# include "asm.h"
# include "op.h"
# include <fcntl.h>

void	print_error(char *str)
{
	ft_printf("%s", str);
	ft_printf("\n");
}

# define CHECK_MODE 0
# define PRINT_MODE 1
# define ERROR_MIN 0
# define ERROR_MAX 30
# define NO_FILE_ERR 0
# define SOURCE_ERR 1
# define MALLOC_ERR 2
# define SIZE_ERROR 3
# define OPEN_ERROR 4
# define FILE_ERROR 5
# define INST_ERROR 6
# define LEX_ERROR 7
# define LABEL_ERROR 8
# define TOO_MUCH_ARG_ERR 9
# define BAD_ARG_REG 10
# define BAD_ARG_DIR 11
# define BAD_ARG_IND 12
# define BAD_ARG_REG_IND 13
# define BAD_ARG_REG_DIR 14
# define BAD_ARG_IND_DIR 15
# define BAD_ARG_REG_DIR_IND 16
# define NAME_SIZE_ERR 17
# define COM_SIZE_ERR 18
# define NAME_EXISTS 19
# define COM_EXISTS 20
# define COMMAND_ERR 21
# define NO_NAME 22
# define NO_COMMENT 23
# define NO_INSTRUCTIONS 24
# define NO_ARGUMENTS 25
# define WRONG_FORM_COM 26
# define SIZE_MAX_ERR 27
# define WRONG_FILE 28
# define NO_COMP 29
# define LAB_EXISTS 30
# define WRONG_MAG 50

typedef struct	s_asm_env
{
	struct s_tab_labs	*labs;
	int					bytes;
	int					size;
	int					fd;
	int					line;
	char				*current_line;
	char				*verbose_line;
	int					name;
	int					comment;
	int					debug;
	int					verbose;
	int					ko;
	int					print;
}				t_asm_env;

typedef struct	s_tab_labs
{
	char				*label;
	int					nb_oct;
	struct s_tab_labs	*next;
}				t_tab_labs;

void	asm_error(int err, char *str)
{
		
		exit(EXIT_FAILURE);
}

void	init_env(t_asm_env *env)
{
	env->name = 0;
	env->comment = 0;
	env->bytes = 1;
	env->line = 1;
	env->ko = 0;
	env->current_line = NULL;
}

void	check_mode(t_asm_env *env, char *name, int fd)
{
	char	*line;

	init_env(env);
	line = NULL;
	env->print = 0;
	env->labs = NULL;
	ft_printf("test check_mode");
	while (get_next_line(fd, &line) > 0)
	{
		env->current_line = line;
		// check_line(env, line);
		// parse(env, line);
	ft_printf("%s loop\n", env->current_line);

		ft_memdel((void*)&line);
		++env->line;
	}
	env->current_line = line;
	if (!env->name)
		asm_error(NO_NAME, NULL);
	if (!env->comment)
		asm_error(NO_COMMENT, NULL);
	if (env->bytes == 1)
		asm_error(NO_INSTRUCTIONS, NULL);
	env->size = env->bytes - 1;
	if (env->size > CHAMP_MAX_SIZE)
		asm_error(SIZE_MAX_ERR, name);
}

int		check_name(char *str)
{
	int size;

	size = ft_strlen(str);
	if (size < 2)
		return (0);
	return (str[size - 2] == '.' && str[size - 1] == 's' ? 1 : 0);
}

void	create_file(t_asm_env *env, char *str)
{
	int		fd;
	int		len;
	char	*tmp;
	char	*name;

	len = ft_strlen(str) - 2;
	if (!(tmp = ft_strndup(str, len)))
		asm_error(MALLOC_ERR, NULL);
	if (!(name = (char*)malloc(sizeof(char) * (len + 4 + 1))))
		asm_error(MALLOC_ERR, NULL);
	name[len + 4] = '\0';
	name = ft_strcpy(name, tmp);
	name = ft_strcat(name, ".cor");
	ft_printf("%s\n", name);

	fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	ft_memdel((void*)&name);
	ft_memdel((void*)&tmp);
	env->fd = fd;
}

void	loop_args(t_asm_env *env, char **argv, int arg)
{
	int fd;

	if ((fd = open(argv[arg], O_RDONLY)) == -1)
		asm_error(SOURCE_ERR, argv[arg]);
	if (!check_name(argv[arg]))
		asm_error(FILE_ERROR, argv[arg]);
	ft_printf("%s\n", argv[arg]);
	check_mode(env, argv[arg], fd);
	ft_printf("test");
	create_file(env, argv[arg]);

}


int		main(int argc, char **argv)
{

	t_asm_env	env;
	int			arg;
	
	if (argc == 1)
	{
		ft_printf("Usage : ./asm {*.cor}\n");
		asm_error(NO_FILE_ERR, NULL);
	}



	if (argc == 1)
		asm_error(NO_FILE_ERR, NULL);
	while (arg < argc)
	{
		loop_args(&env, argv, arg);
		++arg;
	}
	return (0);
}
