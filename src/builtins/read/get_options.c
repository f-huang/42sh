/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:05:40 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/14 20:06:52 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_read.h"
#include "libft.h"
#include "ft_42sh.h"

static int		acquaint_option(t_read *tools, char **av, int *i, int *j)
{
	static int	(*p[5])(t_read *, char **, int *, int *);

	p[0] = read_option_d;
	p[1] = read_option_n;
	p[2] = read_option_p;
	p[3] = read_option_t;
	p[4] = read_option_u;
	const char	options[] = "dnptu";
	int			x;

	x = -1;
	while (options[++x])
		if (options[x] == av[*i][*j])
		{
			(*j)++;
			return ((p[x])(tools, av, i, j) ? 1 : -1);
		}
	return (0);
}

static int		is_option(t_read *tools, char **av, int *i, int *j)
{
	const char	options[] = "dnptu";
	int			x;

	x = 0;
	while (options[x])
	{
		if (options[x] == av[*i][*j])
		{
			if (acquaint_option(tools, av, i, j) == -1)
				return (-1);
			return (x);
		}
		x++;
	}
	if (av[*i][*j] == 'e')
		tools->option |= OPTION_E;
	else if (av[*i][*j] == 'r')
		tools->option |= OPTION_R;
	else if (av[*i][*j] == 's')
		tools->option |= OPTION_S;
	else
	{
		ft_putstr_fd("42sh: bad option: -", 2);
		ft_putchar_fd(av[*i][*j], 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	return (5);
}

int				read_get_options(char **av, t_read *tools)
{
	int			i;
	int			j;
	int			ret;

	i = 1;
	while (av[i] && *(av[i]) == '-')
	{
		if (ft_strequ(av[i], "--"))
			return (++i);
		j = 1;
		while (av[i] && av[i][j])
		{
			if ((ret = is_option(tools, av, &i, &j) == -1))
				return (-1);
			if (ret < 5)
				break ;
			if (av[i] && av[i][j])
				j++;
		}
		if (av[i])
			i++;
	}
	return (i);
}
