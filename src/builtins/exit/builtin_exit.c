/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 09:54:32 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/10 10:09:18 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_42sh.h"

static int	is_str_digit(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (ERROR);
		i++;
	}
	return (GOOD);
}

int     builtin_exit(t_shell *sh, int ac, char **av)
{
	if (ac > 2)
	{
		ft_putendl_fd("42sh: exit: too many arguments.", 2);
		return (1);
	}
	if (av[1] && !is_str_digit(av[1]))
	{
		ft_putstr_fd("42sh: exit: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putendl_fd(": Expression syntax.", 2);
		return (1);
	}
	//CLEAR SHELL
	exit(av[1] ? (char)ft_atoi(av[1]) : EXIT_SUCCESS);
	return (0);
}
