/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_display.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:49:50 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/08 12:50:06 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	ft_remove_display(char *to_add)
{
	size_t	diff;
	size_t	i;

	i = 0;
	diff = cor()->len - cor()->x;
	while (i < diff + 10)
	{
		ft_putchar(' ');
		i++;
	}
	ft_move_left(diff + 10);
	ft_putstr(to_add);
	ft_move_left(ft_strlen(to_add));
}
