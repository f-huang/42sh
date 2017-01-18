/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:49:07 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/18 18:47:10 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
/*
static void	manage_bs(void)
{
	int		bs;
	int		i;

	bs = 0;
	i = 0;
	while (!(*stock()) && (*command())[i])
	{
		
	}
}*/
void		manage_quotes(void)
{
	int		i;
	int		dq;
	int		q;

	i = 0;
	q = 0;
	dq = 0;
//	manage_bs();
	while (!(*stock()) && (*command())[i])
	{
		if ((*command())[i] == '"' && !(q % 2) && !(*bs()))
			dq++;
		if ((*command())[i] == '\'' && !(dq % 2))
			q++;
		i++;
	}
	while ((*stock()) && (*stock())[i])
	{
		if ((*stock())[i] == '"' && !(q % 2) && !(*bs()))
			dq++;
		if ((*stock())[i] == '\'' && !(dq % 2))
			q++;
		i++;
	}
	*(dquote()) = dq;
	*(quote()) = q;
}

void	reset_quotes(void)
{
	*dquote() = 0;
	*quote() = 0;
	*bs() = 0;
}
