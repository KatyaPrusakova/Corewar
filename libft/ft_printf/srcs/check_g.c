/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_g.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 18:59:27 by ksuomala          #+#    #+#             */
/*   Updated: 2021/05/26 13:13:47 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_first_significunt_digit(long double dec, int prelen, char hash)
{
	int	pre;

	pre = 0;
	if (dec >= 1 || (dec > 0 && dec < 1))
		pre--;
	while (dec < 1 && dec != 0)
	{
		pre++;
		dec *= 10;
	}
	while (dec >= 10 && prelen + pre >= 0)
	{
		dec /= 10;
		pre--;
	}
	if (!dec && hash)
		pre--;
	return (prelen + pre);
}

void	ft_last_exponent(char *s, int *exp)
{
	int	i;

	i = 0;
	if (ft_atoi(s) == 10)
	{
		*exp += 1;
		while (s[i] != '.' && s[i])
			i++;
		if (s[i] == '.')
		{
			s[i] = s[i - 1];
			s[i - 1] = '.';
		}
		while (s[i])
			i++;
		s[i - 1] = '\0';
	}
}

void	ft_nan_inf(t_struct *f)
{
	f->spe->sign = '\0';
	f->spe->zero = 0;
	f->spe->type = '\0';
	f->spe->g = '\0';
}

char	*ft_f_presicion(long double dec, int prelen, t_struct *f)
{
	char	*s;

	s = NULL;
	if (f->spe->type == 'g' && f->spe->p_is && !f->spe->p_len)
		prelen = 1;
	if (f->spe->type == 'g')
		prelen = ft_first_significunt_digit(dec, prelen, f->spe->hash);
	s = ft_dtoa(dec, prelen, 1);
	if (!s)
		return (NULL);
	if (f->spe->type == 'g' && f->spe->hash && !ft_strchr(s, '.'))
		s = ft_strfjoin(s, ft_strdup("."));
	if (!s)
		return (NULL);
	if (f->spe->type == 'e' || f->spe->g == 'e')
	{
		ft_last_exponent(s, &f->spe->exponent);
		s = ft_add_postfix(f, s);
	}
	f->spe->convert = ft_replace_ptr(s, f->spe->convert);
	return (f->spe->convert);
}
