/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_options.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 20:20:21 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/10 16:54:53 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "libft.h"

/*
**		This file looks if the right options are given.
**		If not it returns ERROR and option array is cleared.
**		Else the corresponding index of the array is set to 1.
**		index 0 stands for the newline and index 1 for escaped characters.
*/

static int	is_option(_Bool option[2], char c)
{
	const char	letters[] = "Een";
	int			i;

	i = 0;
	while (letters[i])
	{
		if (c == letters[i])
		{
			if (i == 2)
				option[0] = 1;
			else if (i == 1)
				option[1] = 1;
			else
				option[1] = 0;
			return (GOOD);
		}
		i++;
	}
	return (ERROR);
}

int			check_for_options(_Bool option[2], char *str)
{
	static int	good = 0;
	int			i;

	i = 1;
	if (str[i] == 0)
		return (ERROR);
	while (str[i])
	{
		if (!is_option(option, str[i]))
		{
			if (!good)
				ft_bzero(option, sizeof(_Bool) * 2);
			return (ERROR);
		}
		i++;
	}
	good = 1;
	return (GOOD);
}
