/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_jump_to_other_quote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 20:14:18 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/25 20:25:50 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	tl_jump_to_other_quote(char *ptr)
{
	char	c;
	size_t	i;

	i = 1;
	c = ptr[i];
	while (ptr[i] && ptr[i] != c && ptr[i - 1] != '\\')
		i++;
	return (i);
}
