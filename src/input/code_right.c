/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:32:38 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/08 12:32:52 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	code_right(void)
{
	int	check;

	check = cor()->x < cor()->len;
	if (check)
		(cor()->x)++;
	if (check && ((cor()->x + cor()->prompt_len) % ft_termsize()->col))
		ft_move_right(1);
	else if (check && !((cor()->x + cor()->prompt_len) % ft_termsize()->col))
	{
		ft_move_down(1);
		ft_move_left(ft_termsize()->col - 1);
	}
}
