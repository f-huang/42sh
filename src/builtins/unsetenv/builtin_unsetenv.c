/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:56:25 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/09 18:01:20 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_unsetenv.h"

int			builtin_unsetenv(t_shell *sh, int ac, char **av)
{
	if (ac == 1)
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
	else
	{
		while (ac-- >= 1)
			sh_unsetenv(&sh->lst_env, av[ac]);
	}
	return (GOOD);
}
