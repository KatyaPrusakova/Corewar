/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 18:41:34 by mlink             #+#    #+#             */
/*   Updated: 2021/12/25 00:55:46 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"

static void	skip_space(char *line, char *reform, int *i, int *pos)
{
	reform[*pos] = ' ';
	*pos += 1;
	while (line[*i] == ' ' || line[*i] == '\t')
		*i += 1;
	*i -= 1;
}

static char	*reduce_whitespace(char *line, char *reform, int *i, int *pos)
{
	while (line[*i])
	{
		if (line[*i] == COMMENT_CHAR || line[*i] == ALT_COMMENT_CHAR)
		{
			line[*i] = '\0';
			break ;
		}
		if (line[*i] != ' ' && line[*i] != '\t')
		{
			if ((line[*i] == DIRECT_CHAR || line[*i] == '-') && \
				line[*i - 1] != ' ' && line[*i - 1] != '\t' && \
				line[*i - 1] != SEPARATOR_CHAR)
			{
				reform[*pos] = ' ';
				*pos += 1;
			}
			reform[*pos] = line[*i];
			*pos += 1;
		}
		else
			skip_space(line, reform, i, pos);
		*i += 1;
	}
	if (reform[*pos - 1] == ' ')
		*pos -= 1;
	return (reform);
}

static char	*final_reformat(char *reform, int *i, int *pos, int separator)
{
	char	*final;

	if (!(final = (char*)malloc(sizeof(char) * ft_strlen(reform) + 2)))
		ft_error(ERR_MALLOC_STR);
	while (reform[*pos])
	{
		if (reform[*pos] != ' ')
		{
			final[*i] = reform[*pos];
			*i += 1;
		}
		else if (reform[*pos] == ' ' && !separator)
		{
			(reform[*pos - 1] == LABEL_CHAR) ? (final[*i] = SEPARATOR_CHAR) : 0;
			if (ft_isalpha(reform[*pos - 1]) && !separator)
			{
				final[*i] = SEPARATOR_CHAR;
				separator = 1;
			}
			*i += 1;
		}
		*pos += 1;
	}
	ft_strdel(&reform);
	return (final);
}

char	*reformat(char *line)
{
	int		i;
	int		pos;
	char	*reform;

	i = 0;
	pos = 0;
	if (!(reform = (char*)malloc(sizeof(char) * ft_strlen(line) + 2)))
		ft_error(ERR_MALLOC_STR);
	reform = reduce_whitespace(line, reform, &i, &pos);
	reform[pos] = '\0';
	pos = 0;
	i = 0;
	reform = final_reformat(reform, &i, &pos, 0);
	reform[i] = SEPARATOR_CHAR;
	reform[i + 1] = '\0';
	return (reform);
}
