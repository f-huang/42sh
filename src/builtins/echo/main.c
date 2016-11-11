/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 20:20:27 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/11 17:53:50 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_echo.h"
#include "ft_42sh.h"
#include <unistd.h>

int			main(int ac, char **av)
{
	_Bool	is_option;
	_Bool	option[2];
	int		i;

	i = 1;
	is_option = 1;
	ft_bzero(option, sizeof(_Bool) * 2);
	while (av[i])
	{
		if (is_option && *av[i] == '-' &&\
			((is_option = echo_check_for_options(option, av[i]))))
			i++;
		else
		{
			if (!echo_strings(option, av[i]))
				return (1);
			if (av[++i] && write(1, " ", 1) == -1)
				return (1);
		}
	}
	if (!option[0] && write(1, "\n", 1) == -1)
		return (1);
	(void)ac;
	return (0);
}
