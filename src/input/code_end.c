/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <ataguiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/25 17:34:26 by ataguiro          #+#    #+#             */
/*   Updated: 2017/02/05 14:04:51 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	code_end(void)
{
	while (cor()->x < cor()->len)
	{
		//
		if (cor()->x
				&& cor()->prompt_len
				&& termsize()->col
				&& !((cor()->x + cor()->prompt_len) % termsize()->col))
/*=======
		if (termsize()->col != 0 &&\
			!((cor()->x + cor()->prompt_len) % termsize()->col))
>>>>>>> 786ad1e79dd89d8f78df827f4ee87603c36086c4*/
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
