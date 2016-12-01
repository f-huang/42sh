/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:48:58 by cjacquem          #+#    #+#             */
/*   Updated: 2016/12/01 18:44:30 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*tl_strndup(const char *s1, size_t n)
{
	char *s2;

	if (!(s2 = ft_memalloc(n + 1)))
		return (NULL);
	return (ft_strncat(s2, s1, n));
}
