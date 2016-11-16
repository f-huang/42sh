/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcaps.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 17:17:00 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/16 11:40:38 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TERMCAPS_H
# define FT_TERMCAPS_H

typedef struct termios t_termios;
typedef struct winsize t_winsize;

int			init_termios(t_termios *term, t_winsize *window);
int			reset_termios(t_termios *term);

#endif
