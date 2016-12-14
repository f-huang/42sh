/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 11:51:06 by cjacquem          #+#    #+#             */
/*   Updated: 2016/12/14 19:59:24 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_read.h"
#include "libft.h"
#include "ft_42sh.h"
#include <curses.h>
#include <term.h>
#include <sys/ioctl.h>

void	debug_options(t_read tools)
{
	if (tools.option & OPTION_D)
	{
		ft_putstrcol("d -> ", CYAN);
		ft_putendlcol(&tools.delim, YELLOW);
	}
	if (tools.option & OPTION_E)
		ft_putstrcol("e", CYAN);
	if (tools.option & OPTION_N)
	{
		ft_putstrcol("n -> ", CYAN);
		ft_putnbrendl(tools.nchars);
	}
	if (tools.option & OPTION_P)
	{
		ft_putstrcol("p -> ", CYAN);
		ft_putendlcol(tools.prompt, YELLOW);
	}
	if (tools.option & OPTION_R)
		ft_putstrcol("r", CYAN);
	if (tools.option & OPTION_S)
		ft_putstrcol("s", CYAN);
	if (tools.option & OPTION_T)
	{
		ft_putstrcol("t -> ", CYAN);
		ft_putnbrendl(tools.timeout);
	}
	if (tools.option & OPTION_U)
	{
		ft_putstrcol("u -> ", CYAN);
		ft_putnbrendl(tools.fd);
	}
}

int		builtin_read(t_shell *sh, int ac, char **av)
{
	int			i;
	t_read		tools;
	// int			option;

	ft_bzero(&tools, sizeof(t_read));
	if ((i = read_get_options(av, &tools)) == -1)
		return (1);
	// if (!(option & OPTION_S))
		// reset_termios(&term);
	debug_options(tools);
	// if (!(option & OPTION_S))
		// init_termcaps(&term, &window);
	(void)sh;
	(void)ac;
	return (0);
}
