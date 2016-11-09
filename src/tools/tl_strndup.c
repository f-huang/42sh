/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:48:58 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/09 17:49:00 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*tl_strndup(const char *s1, size_t n)
{
	char *s2;

	if (!(s2 = ft_strnew(n)))
		return (NULL);
	return (ft_strncat(s2, s1, n));
}
