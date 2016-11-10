/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:47:48 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/10 12:36:04 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "environment.h"
#include "libft.h"
#include "tools.h"

static int	check_validity_av(char *argv)
{
	if (!ft_isalpha(*argv))
	{
		ft_putendl_fd("setenv: Variable name must begin with a letter.", 2);
		return (ERROR);
	}
	else if (!tl_strisalnum(argv))
	{
		ft_putstr_fd("setenv: ", 2);
		ft_putendl_fd("Variable name must contain alphanumeric characters.", 2);
		return (ERROR);
	}
	return (GOOD);
}

int			builtin_setenv(t_shell *sh, int ac, char **av)
{
	if (ac == 1)
		sh_print_env(sh->lst_env);
	else if ((ac == 2 || ac == 3)
	{
		if (!check_validity_av(av[1]))
			return (ERROR);
		sh_setenv(&sh->lst_env, av[1], av[2]);
	}
	else if (ac > 3)
	{
		ft_putendl_fd("setenv: Too many arguments.", 2);
		return (ERROR);
	}
	return (GOOD);
}
