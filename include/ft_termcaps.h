/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcaps.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 17:17:00 by cjacquem          #+#    #+#             */
/*   Updated: 2016/12/08 14:38:37 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TERMCAPS_H
# define FT_TERMCAPS_H

# include "ft_42sh.h"

typedef struct termios	t_termios;
typedef struct winsize	t_winsize;

int			init_termios(t_termios term, t_winsize *window);
int			reset_termios(t_termios term);

#endif
