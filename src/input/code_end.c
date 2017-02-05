/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <ataguiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/25 17:34:26 by ataguiro          #+#    #+#             */
/*   Updated: 2017/02/05 13:23:34 by ataguiro         ###   ########.fr       */
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
>>>>>>> b11c8af03a15b64c435e5c9b63bfb46f1256c08e*/
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
