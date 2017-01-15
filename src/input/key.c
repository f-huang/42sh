/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:44:58 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/15 12:48:01 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	key_dump(int key)
{
	(key == CODE_TAB) ? completion() : 0;
	(key == CODE_UP) ? code_up(key) : 0;
	(key == CODE_BACK) ? stremove() : 0;
	(key == CODE_RIGHT) ? code_right() : 0;
	(key == CODE_LEFT) ? code_left() : 0;
	(key == CODE_DOWN) ? code_down(key) : 0;
	(key == CODE_CTRL_D) ? code_ctrl_d() : 0;
	(key == CODE_RETURN) ? code_return(&key) : 0;
	(key == CODE_HOME) ? code_home() : 0;
	(key == CODE_END) ? code_end() : 0;
	(key == CODE_SHIFT_UP) ? code_shift_up() : 0;
	(key == CODE_SHIFT_DOWN) ? code_shift_down() : 0;
	(key == CODE_SHIFT_RIGHT) ? code_shift_right() : 0;
	(key == CODE_SHIFT_LEFT) ? code_shift_left() : 0;
	(key == CODE_CTRL_X) ? code_ctrl_x() : 0;
	(key == CODE_CTRL_U) ? code_ctrl_u() : 0;
	(key == CODE_CTRL_W) ? code_ctrl_w() : 0;
	(key == CODE_CTRL_L) ? code_ctrl_l() : 0;
}

int		key_get(void)
{
	char	c;

	raw_mode();
	read(0, &c, 1);
	if (!ft_isvalid(c))
		return (-3);
	if (c == '\x01')
		return (CODE_HOME);
	if (c == '\x05')
		return (CODE_END);
	if (c == '\x9' || c == '\x4' || c == '\x18' || c == '\x15' || c == '\x17' ||
	c == '\x7f' || (c == '\xa' && !(*bs())) || c == '\x0c')
		return (get_basics(c));
	if (c == '\x1b')
	{
		read(0, &c, 1);
		return (get_x1b(c));
	}
	manage_command(c);
	if (ft_getlast(*command()) == '\\')
		(*bs()) = 1;
	else
		(*bs()) = 0;
	return (-2);
}
