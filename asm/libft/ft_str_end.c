/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlink <mlink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:50:34 by mlink             #+#    #+#             */
/*   Updated: 2021/09/25 14:48:01 by mlink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_end(const char *src_1, const char *src_2)
{
	size_t src_l1;
	size_t src_l2;

	src_l1 = ft_strlen(src_1);
	src_l2 = ft_strlen(src_2);
	return (src_l2 <= src_l1 && ft_strequ(src_1 + src_l1 - src_l2, src_2));
}
