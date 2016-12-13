/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_getkey.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 12:19:57 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/13 12:35:05 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "libft.h"

char		*var_getkey(char *variable)
{
	char	*tmp;

	if ((tmp = ft_strchr(variable, '=')))
		return (ft_strndup(variable, (size_t)(tmp - variable)));
	return (NULL);
}
