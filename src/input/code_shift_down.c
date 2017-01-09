/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_shift_down.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:33:03 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/08 12:33:10 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	code_shift_down(void)
{
	size_t	t;

	t = cor()->x + ft_termsize()->col;
	while (cor()->x <= cor()->len && cor()->x <= t)
	{
		if (!((cor()->x + cor()->prompt_len) % ft_termsize()->col))
		{
			ft_move_down(1);
			ft_move_left(ft_termsize()->col - 1);
			ft_move_right(1);
		}
		else
			ft_move_right(1);
		(cor()->x)++;
	}
	ft_move_left(1);
	(cor()->x)--;
}
