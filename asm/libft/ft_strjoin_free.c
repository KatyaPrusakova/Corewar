/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 13:12:50 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/02 13:13:01 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*str;

	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * len1 + len2 + 1);
	if (!str)
		return (0);
	i = -1;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	i = 0;
	while (s2[i] != '\0')
		str[len1++] = s2[i++];
	str[len1] = '\0';
	if (s1 && s2)
	{
		free(s1);
		free(s2);
	}
	return (str);
}
