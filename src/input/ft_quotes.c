/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:49:07 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/08 12:49:37 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	ft_manage_quotes(void)
{
	int		i;
	int		dq;
	int		q;

	i = 0;
	q = 0;
	dq = 0;
	while ((*command())[i])
	{
		if ((*command())[i] == '"' && !(q % 2))
			dq++;
		if ((*command())[i] == '\'' && !(dq % 2))
			q++;
		i++;
	}
	*(dquote()) = dq;
	*(quote()) = q;
}

void	ft_reset_quotes(void)
{
	*dquote() = 0;
	*quote() = 0;
}
