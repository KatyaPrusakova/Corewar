/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 00:15:09 by katyaprusak       #+#    #+#             */
/*   Updated: 2021/12/20 00:15:12 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (withmalloc(3)) and returns a “fresh” substringfrom the string
** given as argument. The substring begins at indexstart and is of sizelen.
** If start and len aren’t refer-ing to a valid substring, or the allocation
** fails, the function returns NULL.
*/

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	ptr = ft_strnew(len);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (!s[i + start])
		{
			free(ptr);
			return (NULL);
		}
		ptr[i] = s[i + start];
		i++;
	}
	return (ptr);
}
