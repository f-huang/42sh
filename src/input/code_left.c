/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_left.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:32:08 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/08 12:32:12 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	code_left(void)
{
	if (cor()->x > 0)
	{
		(cor()->x)--;
		move_left(1);
	}
}
