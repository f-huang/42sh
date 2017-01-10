/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <ataguiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 15:25:34 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/08 12:56:10 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*ft_strdup_input(char *src)
{
	int		i;
	int		j;
	int		n;
	char	*dest;

	i = 0;
	n = 0;
	j = 0;
	while (src && src[n])
		n++;
	if (!n)
		return (ft_strnew(0));
	dest = ft_strnew(n + 1);
	while (src[i])
	{
		if ((unsigned char)src[i] != 127)
		{
			dest[j] = src[i];
			j++;
		}
		i++;
	}
	dest[j] = '\0';
	return (dest);
}
