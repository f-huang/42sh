/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 17:18:21 by fhuang            #+#    #+#             */
/*   Updated: 2016/06/12 20:25:05 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_nbrlen(int n)
{
	size_t		size;

	size = 1;
	ABS(n);
	while (n / 10)
	{
		n /= 10;
		size++;
	}
	return (size);
}
