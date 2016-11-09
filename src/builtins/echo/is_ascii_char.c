/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ascii_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 20:20:25 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/09 20:40:17 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_42sh.h"

/*
**	This function prints the escaped characters when ascii octal or/and hexadecimal
**	codes are in the string.
*/

int		are_char_digits(char *str)
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

// int		is_hexa_char(char *str)
// {
// 	char	*buffer;
//
// 	// ft_putendlcol("hexa char", RED);
// 	if (!(buffer = are_char_digits(str)))
// 		return (ERROR);
// 	// ft_putendlcol(buffer, GREEN);
// 	// ft_atoi(buffer);
// 	// write(1, ft_atoi(buffer), 1);
// 	// printf("%x", (unsigned char)(ft_atoi(buffer)));
// 	return (GOOD);
// }


int		is_ascii_char(char *str)
{
	if (*str == 'x')
	{
		if (!ft_isdigit(*(str + 1)))
			return (ERROR);
		if (write(1, str - 1, 1) == -1)
			return (ERROR);
		// return (GOOD);
	}
	else if (are_char_digits(str))
	{
		if (write(1, str, 3) == -1)
			return (ERROR);
	}
	else
		return (ERROR);

	// else
		// return (is_octal_char(str));
	return (GOOD);
}
