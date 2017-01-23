/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 18:38:30 by fhuang            #+#    #+#             */
/*   Updated: 2017/01/23 21:47:17 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tools.h"
#include "input.h"

int		is_a_command(char *command)
{
	size_t	i;

	if (tl_isstrempty(command))
		return (1);
	i = cor()->x - 1;
	while (i > 0)
	{
		if (!tl_iswhitespace(command[i]) && command[i] != ';')
			return (0);
		return (1);
	}
	return (1);
}
