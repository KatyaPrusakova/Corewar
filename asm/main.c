/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katyaprusakova <katyaprusakova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 19:32:33 by katyaprusak       #+#    #+#             */
/*   Updated: 2021/09/23 20:10:01 by katyaprusak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../libft/ft_printf/includes/ft_printf.h"
#include "../includes/error.h"
#include "../includes/op.h"


void	print_error(char *str)
{
	ft_printf("%s", str);
	ft_printf("\n");
}

int		main(int argc, char **argv)
{

	int			i;

	i = 0;
	
	if (argc > 1)
	{
		while (++i < argc)
        ft_printf("\n");
        ft_printf("%s test", argv[i]);
			// get_player_code(argv[i], &players);
	}
	else
		print_error("Not valid input");
	return (0);
}
