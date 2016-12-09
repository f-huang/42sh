/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:05:40 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/09 17:20:16 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_read.h"

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

static int		is_option(char *av, int *option)
{
	const char	options[] = "denprstu";
	int			i;
	int			j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (options[j])
		{
			if (av[i] != option[j])
			{
				ft_putstr_fd("42sh: bad option: -", 2)
				ft_putchar_fd(av[i], 2);
				ft_putchar_fd('\n', 2);
				return (0);
			}
			acquaint_option(option, option[j]);
			j++;
		}
		i++;
	}
	return (1);
}

int				get_options(char **av, int *option)
{
	int			i;

	i = 1;
	if (ft_strequ(av[i], "--"))
		return (++i);
	while (av[i] && *(av[i]) == '-')
	{
		if (!is_option(av[i]))
			return (-1);
		i++;
	}
	return (i);
}
