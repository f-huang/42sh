/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:32:38 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/23 15:40:23 by tpoac            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	code_right(void)
{
	int	check;

	if (cor()->x && cor()->prompt_len && termsize()->col)
	{
		check = cor()->x < cor()->len;
		if (check)
			(cor()->x)++;
		if (check && ((cor()->x + cor()->prompt_len) % termsize()->col))
			move_right(1);
		else if (check && !((cor()->x + cor()->prompt_len) % termsize()->col))
		{
			move_down(1);
			move_left(termsize()->col - 1);
		}
	}
}
