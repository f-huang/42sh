/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:05:40 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/09 17:36:07 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_read.h"
#include "libft.h"
#include "ft_42sh.h"

static void		acquaint_option(int *option, char c)
{
	if (c == 'd')
		*option |= OPTION_D;
	else if (c == 'e')
		*option |= OPTION_E;
	else if (c == 'n')
		*option |= OPTION_N;
	else if (c == 'p')
		*option |= OPTION_P;
	else if (c == 'r')
		*option |= OPTION_R;
	else if (c == 's')
		*option |= OPTION_S;
	else if (c == 't')
		*option |= OPTION_T;
	else if (c == 'u')
		*option |= OPTION_U;
}

static int		is_option(char c, int *option)
{
	const char	options[] = "denprstu";
	int			i;

	i = 0;
	while (options[i])
	{
		if (options[i] == c)
		{
			acquaint_option(option, c);
			return (GOOD);
		}
		i++;
	}
	ft_putstr_fd("42sh: bad option: -", 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\n', 2);
	return (ERROR);
}

int				get_options(char **av, int *option)
{
	int			i;
	int			j;

	i = 1;
	if (ft_strequ(av[i], "--"))
		return (++i);
	while (av[i] && *(av[i]) == '-')
	{
		j = 1;
		while (av[i][j])
		{
			if (!is_option(av[i][j], option))
				return (-1);
			j++;
		}
		i++;
	}
	return (i);
}
