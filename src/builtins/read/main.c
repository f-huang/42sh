/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 11:51:06 by cjacquem          #+#    #+#             */
/*   Updated: 2016/12/09 17:58:02 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_read.h"
#include "libft.h"
#include "ft_42sh.h"
#include <curses.h>
#include <term.h>
#include <sys/ioctl.h>

void	debug_options(option)
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

static int	init_termcaps(t_termios *term, t_winsize *window)
{
	char			*name_term;

	if (!(name_term = getenv("TERM")))
	{
		ft_putendl_fd("Configure TERM variable environment", 2);
		return (ERROR);
	}
	if (tgetent(NULL, name_term) == ERR)
		return (ERROR);
	if (tcgetattr(0, term) == -1)
		return (ERROR);
	term->c_lflag &= ~(ICANON);
	term->c_lflag &= ~(ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	term->c_cc[VSUSP] = 0;
	if (tcsetattr(0, TCSADRAIN, term) == -1)
		return (ERROR);
	ioctl(0, TIOCGWINSZ, window);
	return (GOOD);
}

static int	reset_termios(t_termios *term)
{
	if (tcgetattr(0, term) == -1)
		return (ERROR);
	term->c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, TCSANOW, term) == -1)
		return (ERROR);
	return (GOOD);
}


int		main(int ac, char **av)
{
	int			i;
	int			option;
	t_termios	term;
	t_winsize	window;

	option = 0;
	ft_bzero(&term, sizeof(term));
	ft_bzero(&window, sizeof(window));
	if ((i = get_options(av, &option)) == -1)
		return (1);
	if (!(option & OPTION_S))
		reset_termios(&term);
	if (!read_input(av, option))
		return (1);
	debug_options(option);
	if (!(option & OPTION_S))
		init_termcaps(&term, &window);
	(void)ac;
	return (0);
}
