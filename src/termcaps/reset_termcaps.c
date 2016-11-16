/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 17:16:08 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/15 17:19:08 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_termcaps.h"

int			reset_termios(t_termios *term)
{
	if (tcgetattr(0, term) == -1)
		return (ERROR);
	term->c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, TCSANOW, term) == -1)
		return (ERROR);
	return (GOOD);
}
