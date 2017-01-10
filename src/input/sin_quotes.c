/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sin_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 13:43:40 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/09 13:45:00 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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
