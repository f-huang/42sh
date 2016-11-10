/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ascii_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 20:20:25 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/10 18:00:34 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tools.h"
#include "ft_42sh.h"

/*
**	This function prints the escaped characters when ascii octal or/and hexadecimal
**	codes are in the string.
*/

static int		are_char_digits(const char *str)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (!ft_isdigit(str[i]))
			return (ERROR);
		i++;
	}
	return (GOOD);
}

int		hex_character(char *str)
{
	int	toto;

	toto = ft_atoi_base(str, 16);
	ft_putchar(toto);
	return (GOOD);
}

int		is_ascii_char(char *str)
{
	ft_putendlcol(str, GREEN);
	if (*str == 'x')
	{
		ft_putendlcol("toto", RED);
		if (!ft_isdigit(*(str + 1)))
			return (ERROR);
		hex_character(str + 1);
	}
	else if (are_char_digits(str))
	{
		if (write(1, str, 3) == -1)
			return (ERROR);
	}
	else
		return (ERROR);
	return (GOOD);
}
