/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 11:51:06 by cjacquem          #+#    #+#             */
/*   Updated: 2016/12/15 17:38:19 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_read.h"
#include "libft.h"
#include "ft_42sh.h"
#include "tools.h"
#include <sys/select.h>

static int	launch_read(t_shell *sh, t_read tools, char **av, int i)
{
	char			*line;

	line = NULL;
	if (!read_input(sh, tools, &line))
		return (ERROR);
	split_line_into_fields(sh, av + i, line);
	ft_strdel(&line);
	return (GOOD);
}

static int	read_start_timer(t_shell *sh, t_read tools, char **av, int i)
{
	struct timeval	tv;
	fd_set			rfds;
	int				ret;

	FD_ZERO(&rfds);
	FD_SET(tools.option & OPTION_U ? tools.fd : 0, &rfds);
	tv.tv_sec = tools.timeout;
	tv.tv_usec = 0;
	if ((ret = select(1, &rfds, NULL,NULL, &tv)) > 0)
	{
		return (launch_read(sh, tools, av, i));
	}
	else
	{
		/* handle line display */
		return (ERROR);
	}
}

int		builtin_read(t_shell *sh, int ac, char **av)
{
	int				i;
	t_read			tools;

	ft_bzero(&tools, sizeof(t_read));
	if ((i = read_get_options(av, &tools)) == -1)
		return (1);
	if (tools.option & OPTION_T)
	{
		if (!read_start_timer(sh, tools, av, i))
			return (1);
	}
	else
		if (!launch_read(sh, tools, av, i))
			return (1);
	(void)ac;
	return (0);
}
