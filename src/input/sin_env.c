/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sin_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 13:42:03 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/15 17:58:09 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include "input.h"

char		**get_home(void)
{
	static char	*get_home = NULL;

	return (&get_home);
}

char		**user(void)
{
	static char	*user = NULL;

	return (&user);
}

t_termsize	*termsize(void)
{
	static t_termsize	new;
	struct winsize		w;

	ioctl(0, TIOCGWINSZ, &w);
	new.col = w.ws_col;
	new.row = w.ws_row;
	return (&new);
}
