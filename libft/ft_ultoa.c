/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlink <mlink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 18:30:51 by mlink             #+#    #+#             */
/*   Updated: 2021/09/25 18:30:55 by mlink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static short	ft_ulonglen(unsigned long n)
{
	size_t cnt;

	cnt = (n <= 0 ? 1 : 0);
	while (n != 0)
	{
		n = n / 10;
		cnt = cnt + 1;
	}
	return (cnt);
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
