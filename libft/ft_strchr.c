/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 11:25:39 by ksuomala          #+#    #+#             */
/*   Updated: 2021/12/05 17:28:50 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The strchr() function returns a pointer to the first occurrence of
** the character c in the string s. If c is not found in *s or *s is NULL,
** NULL is returned.
*/

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
	}
	if (s[i] == c)
		return ((char *)&s[i]);

	return (NULL);
}
