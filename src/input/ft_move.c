/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:48:38 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/08 12:48:53 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	ft_move_left(int x)
{
	if (!x)
		return ;
	ft_putstr("\033[");
	ft_putnbr(x);
	ft_putstr("D");
}

void	ft_move_right(int x)
{
	if (!x)
		return ;
	ft_putstr("\033[");
	ft_putnbr(x);
	ft_putstr("C");
}

void	ft_move_down(int x)
{
	if (!x)
		return ;
	ft_putstr("\033[");
	ft_putnbr(x);
	ft_putstr("B");
}

void	ft_move_up(int x)
{
	if (!x)
		return ;
	ft_putstr("\033[");
	ft_putnbr(x);
	ft_putstr("A");
}
