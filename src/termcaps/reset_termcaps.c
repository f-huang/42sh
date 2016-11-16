/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 17:16:08 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/16 11:45:53 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <term.h>
#include <curses.h>
#include "ft_42sh.h"
#include "ft_termcaps.h"
#include "libft.h"

int			reset_termios(t_termios *term)
{
	if (tcgetattr(0, term) == -1)
		return (ERROR);
	term->c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, TCSANOW, term) == -1)
		return (ERROR);
	return (GOOD);
}
