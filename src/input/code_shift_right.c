/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_shift_right.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:33:30 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/08 12:33:40 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	code_shift_right(void)
{
	if (cor()->x < cor()->len)
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
	while (!(!ft_isspace((*command())[cor()->x - 1]) &&
				ft_isspace((*command())[cor()->x])) && cor()->x < cor()->len)
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
}
