/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/25 17:34:26 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/08 12:30:59 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	code_end(void)
{
	while (cor()->x < cor()->len)
	{
		if (!((cor()->x + cor()->prompt_len) % termsize()->col))
		{
			move_down(1);
			move_left(termsize()->col - 1);
			move_right(1);
		}
		else
			move_right(1);
		(cor()->x)++;
	}
}
