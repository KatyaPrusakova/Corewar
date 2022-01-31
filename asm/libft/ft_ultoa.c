/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 18:30:51 by mlink             #+#    #+#             */
/*   Updated: 2021/12/20 00:03:27 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static short	ft_ulonglen(unsigned long n)
{
	size_t i;

	i = (n <= 0 ? 1 : 0);
	while (n != 0)
	{
		n = n / 10;
		i = i + 1;
	}
	return (i);
}

char			*ft_ultoa(unsigned long n)
{
	char	*res;
	size_t	len;
	size_t	i;

	len = ft_ulonglen(n);
	if (!(res = ft_strnew(len)))
		return (NULL);
	i = 0;
	if (n == 0)
		res[i] = '0';
	while (n != 0)
	{
		res[len - 1] = (n % 10) + 48;
		n = n / 10;
		len = len - 1;
	}
	return (res);
}
