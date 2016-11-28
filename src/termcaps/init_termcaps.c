/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 17:19:39 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/28 18:16:05 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <termios.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <term.h>
#include <curses.h>
#include "ft_42sh.h"
#include "ft_termcaps.h"

int			init_termios(t_termios term, t_winsize *window)
{
	char			*name_term;

	if (!(name_term = getenv("TERM")))
	{
		ft_putendl_fd("Configure TERM variable environment", 2);
		return (ERROR);
	}
	if (tgetent(NULL, name_term) == ERR)
		return (ERROR);
	if (tcgetattr(0, &term) == -1)
		return (ERROR);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	term.c_cc[VSUSP] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (ERROR);
	ioctl(0, TIOCGWINSZ, window);
	return (GOOD);
}
