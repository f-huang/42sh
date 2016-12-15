/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_t.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 19:37:54 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/15 14:37:39 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_read.h"
#include "libft.h"
#include "ft_42sh.h"
#include "tools.h"

int			read_option_t(t_read *tools, char **av, int *i, int *j)
{
	if (av[*i][*j] == 0)
	{
		(*i)++;
		*j = 0;
	}
	if (av[*i] && av[*i][*j])
	{
		if (tl_isstrdigit(av[*i] + *j))
		{
			tools->option |= OPTION_T;
			tools->timeout = ft_atoi(av[*i] + *j);
			return (GOOD);
		}
		else
			return (read_option_error(av[*i] + *j,\
				"invalid timeout specification"));
	}
	read_option_error("-t", "option requires an argument");
	return (ERROR);
}
