/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 11:51:06 by cjacquem          #+#    #+#             */
/*   Updated: 2016/12/12 14:51:33 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_read.h"
#include "libft.h"
#include "ft_42sh.h"
#include <curses.h>
#include <term.h>
#include <sys/ioctl.h>

void	debug_options(int option)
{
	if (option & OPTION_D)
		ft_putstrcol("d", CYAN);
	else if (option & OPTION_E)
		ft_putstrcol("e", CYAN);
	else if (option & OPTION_N)
		ft_putstrcol("n", CYAN);
	else if (option & OPTION_P)
		ft_putstrcol("p", CYAN);
	else if (option & OPTION_R)
		ft_putstrcol("r", CYAN);
	else if (option & OPTION_S)
		ft_putstrcol("s", CYAN);
	else if (option & OPTION_T)
		ft_putstrcol("t", CYAN);
	else if (option & OPTION_U)
		ft_putstrcol("u", CYAN);
	ft_putchar('\n');
}

int		builtin_read(t_shell *sh, int ac, char **av)
{
	int			i;
	int			option;

	option = 0;
	if ((i = get_options(av, &option)) == -1)
		return (1);
	// if (!(option & OPTION_S))
		// reset_termios(&term);
	debug_options(option);
	// if (!(option & OPTION_S))
		// init_termcaps(&term, &window);
	(void)sh;
	(void)ac;
	return (0);
}
