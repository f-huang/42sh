/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 20:20:23 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/10 18:00:05 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_echo.h"
#include "ft_42sh.h"
#include "libft.h"

#ifndef NB_ESC_CHAR
# define NB_ESC_CHAR 10
#endif

/*
**	This function outputs the given string.
**	If -e is on, escaped characters are treated.
*/

static const t_escaped_char	escaped_char[NB_ESC_CHAR] = {
	{'a', "\a"},
	{'b', "\b"},
	{'e', "\e"},
	{'f', "\f"},
	{'n', "\n"},
	{'r', "\r"},
	{'t', "\t"},
	{'v', "\v"},
	{'\\', "\\"},
	{'0', "\0"}
};

static int	echo_escaped_char(char c)
{
	int		i;

	i = 0;
	while (i < NB_ESC_CHAR)
	{
		if (c == escaped_char[i].c)
		{
			if (write(1, escaped_char[i].escaped_char, 1) == -1)
				return (ERROR);
			return (GOOD);
		}
		i++;
	}
	return (ERROR);
}

int			echo_strings(_Bool option[2], char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (option[1] && str[i] == '\\')
		{
			/*
			** Check for \xNNN and \nnn
			*/
			if (!is_ascii_char(str + ++i))
				echo_escaped_char(str[i]) ? 0 : i--;
		}
		else if (str + i && write(1, str + i, 1) == -1)
			return (ERROR);
		i++;
	}
	return (GOOD);
}
