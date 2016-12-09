/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 11:51:06 by cjacquem          #+#    #+#             */
/*   Updated: 2016/12/09 17:20:17 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_read.h"

// void	debug_options(option)
// {
// 	if (*option & OPTION_D)
// 		ft_putstrcol("d", )
// }

int		main(int ac, char **av)
{
	int		i;
	int		option;

	option = 0;
	if ((i = get_options(av, &option)) == -1)
		return (1);
	while (av[i])
	{
		i++;
	}
	(void)ac;
	debug_options(option);
	return (0);
}
