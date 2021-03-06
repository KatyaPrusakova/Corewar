/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 19:21:30 by katyaprusak       #+#    #+#             */
/*   Updated: 2021/09/11 19:21:31 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

long long	ft_atoi(const char *str)
{
	size_t		i;
	long long	ret;
	int			neg;

	if (str == NULL)
		return (0);
	i = 0;
	neg = 1;
	ret = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		ret = ret * 10 + (str[i] - 48);
		i++;
	}
	return (ret * neg);
}
