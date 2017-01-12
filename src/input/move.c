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

#include "input.h"

void	move_left(int x)
{
	if (!x)
		return ;
	ft_putstr("\033[");
	ft_putnbr(x);
	ft_putstr("D");
}

void	move_right(int x)
{
	if (!x)
		return ;
	ft_putstr("\033[");
	ft_putnbr(x);
	ft_putstr("C");
}

void	move_down(int x)
{
	if (!x)
		return ;
	ft_putstr("\033[");
	ft_putnbr(x);
	ft_putstr("B");
}

void	move_up(int x)
{
	if (!x)
		return ;
	ft_putstr("\033[");
	ft_putnbr(x);
	ft_putstr("A");
}