/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits_s.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 22:45:04 by ksuomala          #+#    #+#             */
/*   Updated: 2021/09/11 19:21:46 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_digits_s(char *s)
{
	int	i;
	int	digits;

	digits = 0;
	i = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]))
			digits++;
		i++;
	}
	return (digits);
}
