/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sin_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 13:43:40 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/13 12:24:56 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int		*dquote(void)
{
	static int	dquote = 0;

	return (&dquote);
}

int		*quote(void)
{
	static int	quote = 0;

	return (&quote);
}

int		*bs(void)
{
	static int	bs = 0;

	return (&bs);
}
