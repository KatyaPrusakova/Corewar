/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 16:02:33 by mlink             #+#    #+#             */
/*   Updated: 2022/02/04 19:31:10 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"

static	char	*norm_strjoin_free(char *ret, char *line)
{
	ret = ft_strjoin(ret, "\n");
	ret = ft_strjoin(ret, line);
	return (ret);
}

static char	*continue_reading(int source_fd)
{
	char	*line;
	char	*ret;
	int		flag;

	flag = 0;
	line = NULL;
	ret = ft_strnew(1);
	while (get_next_line(source_fd, &line) > 0)
	{
		if (ft_strchr(line, '\"'))
		{
			flag = 1;
			ret = norm_strjoin_free(ret, line);
			break ;
		}
		else
			ret = norm_strjoin_free(ret, line);
	}
	if (!flag)
		ft_error(ERR_INC_NAME);
	return (ret);
}

static char	*remove_trailing_spaces(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] != '\"')
		i += 1;
	ret = ft_strncpy(ft_strnew(i), str, i);
	i += 1;
	while (str[i] != '\0')
	{
		if (!ft_isspace(str[i]))
		{
			if (str[i] == COMMENT_CHAR || str[i] == ALT_COMMENT_CHAR)
				break ;
			else
				ft_error(ERR_INV_CHAR);
		}
		i += 1;
	}
	free(str);
	return (ret);
}

int	validate_name_comment(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\"')
	{
		if (line[i] == '\0')
			ft_error(ERR_NO_NAME);
		i += 1;
	}
	return (i);
}

char	*save_name_comment(t_asm **core, char *line)
{
	char	*ret;
	int		i;
	int		pos_start;
	char	*next;

	i = validate_name_comment(line);
	pos_start = i + 1;
	i += 1;
	while (line[i] != '\0' && line[i] != '\"')
		i += 1;
	if (line[i] == '\0')
	{
		ret = ft_strdup(&line[pos_start]);
		next = continue_reading((*core)->source_fd);
		ret = ft_strjoin_free(ret, next);
	}
	else
		ret = ft_strdup(&line[pos_start]);
	return (remove_trailing_spaces(ret));
}
