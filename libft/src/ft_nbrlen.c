/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 17:18:21 by fhuang            #+#    #+#             */
/*   Updated: 2017/01/19 16:22:09 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_nbrlen(int n)
{
	size_t		size;
	int			neg;

	size = 1;
	neg = n < 0 ? 1 : 0;
	ABS(n);
	while (n / 10)
	{
		n /= 10;
		size++;
	}
	return (size + neg);
}